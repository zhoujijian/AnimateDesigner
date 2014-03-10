#include "cocosframe.h"
#include "wx/file.h"

// ######## File Menu Create / Open / Save / Quit Solution ######## //
// ################################################## //

void CocosFrame::OnFileMenuCreateSolution(wxCommandEvent& event) {
	CreateSolutionDialog path(NULL, wxID_ANY, _T("create solution"));
	path.CentreOnScreen();

	if (wxID_OK == path.ShowModal()) {
		if (wxFile::Exists(wxT(path.GetPath().c_str()))) {
			wxLogMessage("solution %s existed!", path.GetPath().c_str());
			return;
		}

		AppendSolutionItem(path.GetPath());

		ResetConfig();
		SaveConfig();
	}
}

void CocosFrame::OnFileMenuOpenSolution(wxCommandEvent& event) {
	wxFileDialog dialog(this, _T("open solution"), wxEmptyString, wxEmptyString, _T("solution(*.lua) |*.lua"));
	dialog.CentreOnParent();

	if (dialog.ShowModal() == wxID_OK) {
		if (LoadConfig(dialog.GetPath())) {
			ApplyConfig();
		}
	}
}

wxTreeItemId CocosFrame::AppendSolutionItem(const string& path) {
	string alias = path.substr(path.find_last_of("\\") + 1);
	wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	root->DeleteAllItems();
	root->AddRoot(_T(alias.c_str()));

	wxFont font;
	font.SetFaceName("Consolas");
	CocosTreeItemData *data = new CocosTreeItemData(CoKind::Solution, path, alias);
	root->SetItemData(root->GetRootItem(), data);
	root->SetItemFont(root->GetRootItem(), font);
	return root->GetRootItem();
}

void CocosFrame::OnSolutionRightClicked(wxTreeEvent& event) {
	wxTreeItemId itemid = event.GetItem();
	wxTreeCtrl *solTreeCtrl = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	CocosTreeItemData *data = itemid.IsOk() ? (CocosTreeItemData*)solTreeCtrl->GetItemData(itemid) : NULL;
	if (!data) {
		wxLogMessage("Data of tree item clicked is NULL!");
	}

	wxMenu menu;
	if (data->GetKind() == CoKind::Solution) {
		menu.Append(ID_SOL_ADD_PROJECT_NEW, _T("new project"));
		menu.AppendSeparator();
		menu.Append(ID_SOL_ADD_PROJECT_EXIST, _T("add projects existing"));
	} else if (data->GetKind() == CoKind::Project) {
		menu.Append(ID_POJ_ADD_ANIMATE_NEW, _T("new animate"));
		menu.AppendSeparator();
		menu.Append(ID_POJ_ADD_FILE_EXIST, _T("add file existing"));
		menu.AppendSeparator();
		menu.Append(ID_POJ_ADD_FILTER, _T("new filter"));
		menu.AppendSeparator();
		menu.Append(ID_POJ_REM_PROJECT, _T("remove"));
	} else if (data->GetKind() == CoKind::Folder) {
// 		menu.Append(ID_FOLDER_ADD_ANIMATE_NEW, _T("new animate"));
// 		menu.AppendSeparator();
// 		menu.Append(ID_FOLDER_ADD_FILE_EXIST, _T("add file existing"));
	} else if (data->GetKind() == CoKind::Filer) {
		menu.Append(ID_FILE_REM_FILE, _T("remove"));
	}
	PopupMenu(&menu, event.GetPoint());
}