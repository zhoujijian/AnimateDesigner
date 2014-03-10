#include "wx/textdlg.h"
#include "wx/file.h"

#include "cocosframe.h"
#include "cocoswindow.h"
#include "luagenerator.h"

BEGIN_EVENT_TABLE(CocosFrame, wxFrame)
	EVT_MENU(wxID_NEW,   CocosFrame::OnFileMenuCreateSolution)
	EVT_MENU(wxID_OPEN,  CocosFrame::OnFileMenuOpenSolution)

	EVT_TREE_ITEM_RIGHT_CLICK(ID_SOLUTION_TREE_CTRL, CocosFrame::OnSolutionRightClicked)

	EVT_MENU(ID_SOL_ADD_PROJECT_NEW,   CocosFrame::OnTreeMenuNewProject)
	EVT_MENU(ID_SOL_ADD_PROJECT_EXIST, CocosFrame::OnTreeMenuAddProject)

	EVT_MENU(ID_POJ_ADD_FILE_EXIST, CocosFrame::OnTreeMenuAddFileExisting)
	EVT_MENU(ID_POJ_ADD_ANIMATE_NEW, CocosFrame::OnTreeMenuNewAnimate)
	EVT_MENU(ID_POJ_REM_PROJECT, CocosFrame::OnTreeMenuRemoveProject)

	EVT_MENU(ID_FILE_REM_FILE, CocosFrame::OnTreeMenuRemoveFile)

	EVT_CLOSE(CocosFrame::OnCocosFrameClose)
END_EVENT_TABLE()

CocosFrame::CocosFrame()
	: wxFrame(NULL, wxID_ANY, _T("Cocos2d"), wxDefaultPosition, wxSize(APP_WINDOW_WIDTH, APP_WINDOW_HEIGH)), solution(NULL)
{
	Init();
}

void CocosFrame::Init() {
	wxMenu *file = new wxMenu();
	file->Append(wxID_NEW,   "&Create\tCtrl+N");
	file->Append(wxID_OPEN,  "&Open\tCtrl+O");

	wxMenuBar *menubar = new wxMenuBar(wxMB_DOCKABLE);
	menubar->Append(file, _T("&File"));
	SetMenuBar(menubar);

	wxPanel *panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(wxColour(200, 200, 200, 255));	
	wxTreeCtrl *solTreeCtrl = new wxTreeCtrl(panel, ID_SOLUTION_TREE_CTRL, wxDefaultPosition, wxSize(190, COCOS2D_WX_WINDOW_HEIGH));
	solTreeCtrl->SetBackgroundColour(wxColour(150, 150, 150, 155));	
 	CocosWindow *cocos = new CocosWindow(panel, ID_COCOS_WINDOW,
		wxDefaultPosition, wxSize(COCOS2D_WX_WINDOW_WIDTH, COCOS2D_WX_WINDOW_HEIGH), wxBORDER_NONE);
 	cocos->SetBackgroundColour(wxColour(200, 200, 200, 150));
 	cocos->Start();

	wxBoxSizer *box_sizer = new wxBoxSizer(wxHORIZONTAL);
	box_sizer->Add(solTreeCtrl);
	box_sizer->Add(cocos);
	panel->SetSizer(box_sizer);
	box_sizer->Fit(panel);

	solTreeCtrl->Connect(ID_SOLUTION_TREE_CTRL, wxEVT_LEFT_DCLICK, wxMouseEventHandler(CocosFrame::OnTreeMenuFileDoubleClicked));
}

void CocosFrame::OnCocosFrameClose(wxCloseEvent& event) {
	CocosWindow *cocos = (CocosWindow*)FindWindow(ID_COCOS_WINDOW);
	if (cocos) {
		cocos->StopCocos();
	}
	event.Skip();
}

wxTreeItemId CocosFrame::AppendTreeItem(const string& paths, CoKind kind, wxTreeItemId parent) {
	string alias = paths.substr(paths.find_last_of("\\") + 1);
	
	if (IsTreeItemRepeated(alias, parent)) {
		wxLogMessage("solution/project/file with path %s, alias %s repeated!", paths.c_str(), alias.c_str());
		wxTreeItemId null;
		return null;
	}

	wxFont font;
	font.SetFaceName("Consolas");
	CocosTreeItemData *itemData = new CocosTreeItemData(kind, paths, alias);

	wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	wxTreeItemId item = root->AppendItem(parent, _T(alias.c_str()));
	root->SetItemFont(item, font);	
	root->SetItemData(item, itemData);
	return item;
}

bool CocosFrame::IsTreeItemRepeated(const string& alias, const wxTreeItemId& parent) {
	wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	if (root->GetChildrenCount(parent) > 0) {
		wxTreeItemIdValue iter;
		wxTreeItemId item = root->GetFirstChild(parent, iter);
		while(item.IsOk()) {
			CocosTreeItemData *data = (CocosTreeItemData*)root->GetItemData(item);
			if (!data) {
				wxLogMessage("Tree item data NULL!");
				break;
			}
			if (data->GetAlias() == alias) { return true; }
			item = root->GetNextChild(item, iter);
		}
	}
	return false;
}

void CocosFrame::ResetConfig() {
	ClearConfig();

	wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	wxTreeItemId solid = root->GetRootItem();
	if (solid.IsOk()) {
		CocosTreeItemData *soldata = (CocosTreeItemData*)root->GetItemData(solid);
		solution = new CoConfig(CoKind::Solution, soldata->GetPath());

		wxTreeItemIdValue iter;
		wxTreeItemId pojid = root->GetFirstChild(solid, iter);
		if (pojid.IsOk()) {
			CocosTreeItemData *pojdata = (CocosTreeItemData*)root->GetItemData(pojid);
			CoConfig *poj = new CoConfig();
			poj->path = pojdata->GetPath();
			solution->folders.push_back(poj);

			wxTreeItemId fileid = root->GetFirstChild(pojid, iter);
			while(fileid.IsOk()) {
				CocosTreeItemData *filedata = (CocosTreeItemData*)root->GetItemData(fileid);
				CoConfig *file = new CoConfig();
				file->path = filedata->GetPath();
				poj->files.push_back(file);

				fileid = root->GetNextChild(fileid, iter);
			}
		}
	}
}

void CocosFrame::SaveConfig() {
	if (!LuaGenerator::generator()->write_solution(*solution)) {
		wxLogMessage("save solution-project config failure!");
	}
}

void CocosFrame::ClearConfig() {
	if (solution) {
		CCAssert(solution->folders.size() <= 1, "only one project supported now");
		delete solution;
		solution = NULL;
	}
}

void CocosFrame::ApplyConfig() {
	AppendSolutionItem(solution->path);

	for (int i = 0; i < solution->folders.size(); ++ i) {
		CoConfig *poj = solution->folders.at(i);
		wxTreeItemId pojitem = AppendProjectItem(poj->path);
		if (pojitem.IsOk()) {
			for (int k = 0; k < poj->files.size(); ++ k) {
				CoConfig *file = poj->files.at(k);
				AppendFileItem(pojitem, file->path);
			}
		}
	}
}

bool CocosFrame::LoadConfig(const char *path) {
	ClearConfig();

	solution = new CoConfig();
	solution->kind = CoKind::Solution;
	if (!LuaGenerator::generator()->read_solution(path, *solution)) {
		wxString info;
		wxLogMessage(_T("Read solution from path %s failure!"), path);
		return false;
	}
	return true;
}

void CocosFrame::DumpCurConfig() {
	wxLogMessage("solution path %s, projects =>", solution->path.c_str());
}

void CocosFrame::OpenSolution(const char *path) {
	bool readed = LuaGenerator::generator()->read_solution(path, *solution);
	if (!readed) {
		wxString info;
		wxLogMessage(_T("Read solution from path %s failure!"), path);
	} else {
		// TODO => display solution to treectrl
	}
}

wxTreeItemId CocosFrame::FindParentProject(wxTreeItemId item) {
	wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	CocosTreeItemData *data = (CocosTreeItemData*)root->GetItemData(item);
	while(data->GetKind() != CoKind::Project && item.IsOk()) {
		item = root->GetItemParent(item);
		data = (CocosTreeItemData*)root->GetItemData(item);
	}
	return item;
}

// ########## Create Solution Dialog ######### //
// #################################### //

IMPLEMENT_DYNAMIC_CLASS(CreateSolutionDialog, wxDialog)

BEGIN_EVENT_TABLE(CreateSolutionDialog, wxDialog)
	EVT_BUTTON(ID_SOLUTION_BROWSEDIR, CreateSolutionDialog::OnBrowseClicked)
	EVT_BUTTON(wxID_OK,               CreateSolutionDialog::OnOkClicked)
END_EVENT_TABLE()

bool CreateSolutionDialog::Create(wxWindow *parent, wxWindowID id,
	const wxString& title,
	const wxPoint& pos /* = wxDefaultPosition */,
	const wxSize& size /* = wxDefaultSize */,
	long style /* = wxDEFAULT_DIALOG_STYLE */,
	const wxString& name /* = wxDialogNameStr */)
{
	if (!wxDialog::Create(parent, id, title, pos, size, style, name)) {
		return false;
	}
	
	LayoutControls();
	return true;
}

void CreateSolutionDialog::LayoutControls() {
	// file sizer layout
	wxStaticText *fileLabel = new wxStaticText(this, wxID_STATIC, "File:");
	wxTextCtrl   *fileText  = new wxTextCtrl(this, ID_SOLUTION_FILE_NAME, wxEmptyString, wxDefaultPosition, wxSize(298, 20));
	wxButton     *browButt  = new wxButton(this, ID_SOLUTION_BROWSEDIR, _T("browse"));

	wxBoxSizer *fileSizer = new wxBoxSizer(wxHORIZONTAL);
	fileSizer->Add(fileLabel);
	fileSizer->Add(fileText);
	fileSizer->Add(browButt);
	
	// ok-cancel sizer layout
	wxButton *ok     = new wxButton(this, wxID_OK,     "Ok",     wxDefaultPosition, wxSize(197.5, 20));
	wxButton *cancel = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(197.5, 20));	

	wxBoxSizer *okCancelSizer = new wxBoxSizer(wxHORIZONTAL);
	okCancelSizer->Add(ok);
	okCancelSizer->Add(cancel);

	// dialog layout
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(fileSizer);
	sizer->Add(okCancelSizer);
	SetSizer(sizer);

	sizer->Fit(this);
}

void CreateSolutionDialog::OnBrowseClicked(wxCommandEvent& evt) {
	wxDirDialog dir(NULL, _T("browse"));
	dir.CentreOnScreen();

	if (dir.ShowModal() == wxID_OK) {
		wxTextCtrl *fileText = (wxTextCtrl*)FindWindow(ID_SOLUTION_FILE_NAME);
		fileText->SetValue(dir.GetPath().Append("\\"));
	}
}

void CreateSolutionDialog::OnOkClicked(wxCommandEvent& evt) {
	wxTextCtrl *fileText = (wxTextCtrl*)FindWindow(ID_SOLUTION_FILE_NAME);
	path = string(fileText->GetValue().c_str());

	string::size_type diroffset = path.find_last_of("\\");
	if (diroffset == string::npos) {
		wxLogMessage("Illegal directory path!");
		return;
	}

	string file = path.substr(diroffset + 1);
	if (file.length() <= 4) {
		wxLogMessage("Illegal file name, should end with (.lua)!");
		return;
	}

	string suffix = path.substr(path.length() - 4);
	if (suffix.compare(".lua") != 0) {
		wxLogMessage("Illegal file name, should end with (.lua)!");
		return;
	}

	if (IsModal()) {
		EndModal(wxID_OK);
	} else {
		SetReturnCode(wxID_OK);
		Show(false);
	}
}

bool CocosTreeItemData::IsAliasSame(const char *s) {
	string suffix = alias.substr(alias.find_last_of(".") + 1);
	return suffix.compare(s) == 0;
}

// ############# CoConfig ##############
// ##################################
CoConfig::~CoConfig() {
	for (int i = 0; i < folders.size(); ++ i) {
		CoConfig *folder = folders.at(i);
		if (folder) { delete folder; }
	}
	folders.clear();

	for (int i = 0; i < files.size(); ++ i) {
		CoConfig *file = files.at(i);
		if (file) { delete file; }
	}
	files.clear();
}