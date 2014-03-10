#include "cocosframe.h"
#include "wx/file.h"

// ########### Add / New / Remove project ########### //
// ##########################################  //

void CocosFrame::OnTreeMenuNewProject(wxCommandEvent& event) {
	if (solution->folders.size() > 0) {
		wxLogMessage("only support one project now!");
		return;
	}

	CreateProjectDialog dialog(NULL, wxID_ANY, "create project");
	dialog.CentreOnScreen();

	if (wxID_OK == dialog.ShowModal()) {
		if (wxFile::Exists(wxT(dialog.GetPath().c_str()))) {
			wxLogMessage("project %s existed!", dialog.GetPath().c_str());
			return;
		}
		AppendProjectItem(dialog.GetPath().c_str());

		ResetConfig();
		SaveConfig();
	}
}

void CocosFrame::OnTreeMenuAddProject(wxCommandEvent& event) {
	wxFileDialog dialog(NULL, _T("add project"), wxEmptyString, wxEmptyString, _T("project |*.lua"));
	dialog.CentreOnScreen();

	if (wxID_OK == dialog.ShowModal()) {
		AppendProjectItem(dialog.GetPath().c_str());

		ResetConfig();
		SaveConfig();
	}
}

void CocosFrame::OnTreeMenuRemoveProject(wxCommandEvent& event) {
	wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	wxTreeItemId selected = root->GetSelection();
	if (selected.IsOk()) {
		root->Delete(selected);

		ResetConfig();
		SaveConfig();
	}
}

wxTreeItemId CocosFrame::AppendProjectItem(const string& path) {
	wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	return AppendTreeItem(path.c_str(), CoKind::Project, root->GetRootItem());
}