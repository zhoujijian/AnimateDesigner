#include "cocosframe.h"
#include "fragment.h"
#include "luagenerator.h"
#include "wx/file.h"

void CocosFrame::OnTreeMenuAddFileExisting(wxCommandEvent& event) {
	wxFileDialog dialog(this, _T("open solution"), wxEmptyString, wxEmptyString, _T("plist(*.plist)|*.plist|animate(*.lua)|*.lua"));
	dialog.CentreOnParent();

	if (dialog.ShowModal() == wxID_OK) {
		if (!wxFile::Exists(dialog.GetPath())) {
			wxLogMessage("file %s you opened not exist!", dialog.GetPath());
		} else {
			wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
			wxTreeItemId parent = root->GetSelection();
			if (parent.IsOk()) {
				wxTreeItemId fileid = AppendFileItem(parent, dialog.GetPath().c_str());
				SaveFileConfig(fileid, "add");
			}
		}
	}
}

void CocosFrame::OnTreeMenuNewAnimate(wxCommandEvent& event) {
	CreateAnimateDialog dialog(NULL, wxID_ANY, "create animate");
	if (dialog.ShowModal() == wxID_OK) {
			wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
			wxTreeItemId parent = root->GetSelection();
			if (parent.IsOk()) {
				wxTreeItemId fileid = AppendFileItem(parent, dialog.GetPath().c_str());
				SaveFileConfig(fileid, "add");
			}
	}
}

void CocosFrame::OnTreeMenuRemoveFile(wxCommandEvent& event) {
	wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	wxTreeItemId selected = root->GetSelection();
	if (selected.IsOk()) {
		CocosTreeItemData *data = (CocosTreeItemData*)root->GetItemData(selected);
		if (data->GetKind() == CoKind::Filer) {
// 			if (data->IsAliasPng()) {
// 				MoveLayer::sharedMoveLayer()->rempng(data->GetPath().c_str());
// 			} else {
// 				
// 			}
			SaveFileConfig(selected, "rem");

			root->Delete(selected);
		}
	}
}

void CocosFrame::OnTreeMenuFileDoubleClicked(wxMouseEvent& event) {
	wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
	wxTreeItemId selected = root->GetSelection();
	CocosTreeItemData *data = selected.IsOk() ? (CocosTreeItemData*)root->GetItemData(selected) : NULL;
	if (data && data->GetKind() == CoKind::Filer) {
		if (data->IsAliasSame("plist")) {
			MoveLayer::sharedMoveLayer()->setplist(data->GetPath().c_str());
		} else {
			// todo => load animate information to display
		}
	}
}

wxTreeItemId CocosFrame::AppendFileItem(wxTreeItemId parent, const string& path) {
	wxTreeItemId fileid = AppendTreeItem(path,CoKind::Filer,  parent);
	return fileid;
}

void CocosFrame::SaveFileConfig(wxTreeItemId fileid, const char *cmd) {
	wxTreeItemId pojid = FindParentProject(fileid);
	if (pojid.IsOk()) {
		wxTreeCtrl *root = (wxTreeCtrl*)FindWindow(ID_SOLUTION_TREE_CTRL);
		CocosTreeItemData *pojdata = (CocosTreeItemData*)root->GetItemData(pojid);
		for (int i = 0; i < solution->folders.size(); ++ i) {
			CoConfig *poj = solution->folders.at(i);
			if (poj->path.compare(pojdata->GetPath()) == 0) {
				CocosTreeItemData *filedata = (CocosTreeItemData*)root->GetItemData(fileid);
				if (strcmp(cmd, "add") == 0) {
					for (int j = 0; j < poj->files.size(); ++ j) {
						if (poj->files[j]->path.compare(filedata->GetPath()) == 0) {
							wxLogMessage("Append file %s to project %s repeated!", filedata->GetPath().c_str(), poj->path.c_str());
							break;
						}
					}
					CoConfig *file = new CoConfig(CoKind::Filer, filedata->GetPath());
					poj->files.push_back(file);
				}
				if (strcmp(cmd, "rem") == 0) {
					bool finded = false;
					for (int j = 0; j < poj->files.size(); ++ j) {
						if (poj->files[j]->path.compare(filedata->GetPath()) == 0) {
							poj->files.erase(poj->files.begin() + j);
							finded = true;
							break;
						}
					}
					if (!finded) {
						wxLogMessage("Remove file %s from project %s failure, not found!", filedata->GetPath().c_str(), poj->path.c_str());
					}
				}

				LuaGenerator::generator()->write_project(*poj);
				break;
			}
		}
	}
}