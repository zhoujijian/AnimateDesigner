#ifndef _COCOS_2D_FRAME_H_
#define _COCOS_2D_FRAME_H_

#include <vector>
#include <string>
#include "wx/wx.h"
#include "wx/treectrl.h"
#include "animatcommon.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

#define ID_SOLUTION_FILE_NAME 100
#define ID_SOLUTION_BROWSEDIR 101

#define ID_SOLUTION_TREECTRL     102
#define ID_SOL_ADD_PROJECT_NEW   103
#define ID_SOL_ADD_PROJECT_EXIST 104
#define ID_ANIMATE_TREECTRL      105

#define ID_POJ_ADD_FILTER      126
#define ID_POJ_ADD_ANIMATE_NEW 127
#define ID_POJ_ADD_FILE_EXIST  128
#define ID_POJ_REM_PROJECT     129

#define ID_FILE_REM_FILE    141
#define ID_FILE_RENAME_FILE 142

#define ID_COCOS_WINDOW 153
#define ID_REFRESH_ANIMATE_TIMER 154

class CocosTreeItemData;

class CocosFrame : public wxFrame {
public:
	CocosFrame();

	void Init();

	// ######## Create / Open / Save Solution
	void OnFileMenuCreateSolution(wxCommandEvent& event);
	void OnFileMenuOpenSolution(wxCommandEvent& event);

	void OnSolutionRightClicked(wxTreeEvent& event);

	void OnTreeMenuNewProject(wxCommandEvent& event);
	void OnTreeMenuAddProject(wxCommandEvent& event);
	void OnTreeMenuRemoveProject(wxCommandEvent& event);

	// ######### New / Add / Remove File
	void OnTreeMenuAddFileExisting(wxCommandEvent& event);
	void OnTreeMenuNewAnimate(wxCommandEvent& event);
	void OnTreeMenuRemoveFile(wxCommandEvent& event);
	void OnTreeMenuFileDoubleClicked(wxMouseEvent& event);

	void OnCocosFrameClose(wxCloseEvent& event);
	void OnTimer(wxTimerEvent& evt);

private:
	void OpenSolution(const char *path);
	void GenAnimTree(wxTreeCtrl *root, const wxTreeItemId& parent, CCNode *cur);
	void TestAnimate(wxTreeCtrl *root, const wxTreeItemId& parent, CCNode *cur);

private:
	bool LoadConfig(const char *path);
	void ClearConfig();
	void ResetConfig();
	void SaveConfig();
	void SaveFileConfig(wxTreeItemId fileid, const char *cmd);
	void ApplyConfig();
	void DumpCurConfig();

	void RemoveProjectFromConfig(const string& alias);
	void AddProjectToConfig(const char *alias, const char *path);

private:
	wxTreeItemId AppendSolutionItem(const string& path);
	wxTreeItemId AppendProjectItem(const string& path);
	wxTreeItemId AppendFileItem(wxTreeItemId parent, const string& path);
	wxTreeItemId AppendTreeItem(const string& path, CoKind kind, wxTreeItemId parent);
	wxTreeItemId FindParentProject(wxTreeItemId item);
	bool IsTreeItemRepeated(const string& alias, const wxTreeItemId& parent);

private:
	CoConfig *solution;
	wxTimer anitimer;

private:
	DECLARE_EVENT_TABLE()
};

class CocosTreeItemData : public wxTreeItemData {
public:
CocosTreeItemData() : kind(CoKind::Filer) { }
CocosTreeItemData(CoKind k, const string& itemPath, const string& itemAlias) : kind(k), path(itemPath), alias(itemAlias) { }

		CoKind GetKind() const { return kind; }
		const string& GetPath() { return path; }
		const string& GetAlias() { return alias; }
		bool IsAliasSame(const char *s);

private:
		CoKind kind;
		string path;
		string alias;
};

class AnimTreeItemData : public wxTreeItemData {
public:
	AnimTreeItemData(bool bone, int id) : isbone(bone), tagid(id) { }

	bool IsBone() const { return isbone; }
	int GetTagid() const { return tagid; }
	const char* GetName() const { return name.c_str(); }
	void SetName(const char *nc) { name = string(nc); }

private:
	int tagid;
	string name;
	bool isbone;
};

class CreateSolutionDialog : public wxDialog {
	DECLARE_DYNAMIC_CLASS(CreateSolutionDialog)
	DECLARE_EVENT_TABLE()

public:
	CreateSolutionDialog() {
		wxDialog::Init();
	}

	CreateSolutionDialog(wxWindow *parent, wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE,
		const wxString& name = wxDialogNameStr)
	{
		wxDialog::Init();

		Create(parent, id, title, pos, size, style, name);
	}

	bool Create(wxWindow *parent, wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE,
		const wxString& name = wxDialogNameStr);

	void OnOkClicked(wxCommandEvent& evt);
	void OnBrowseClicked(wxCommandEvent& evt);

	const string& GetPath() { return path; }

private:
	void LayoutControls();

private:
	string path;
};

typedef CreateSolutionDialog CreateProjectDialog;
typedef CreateSolutionDialog CreateAnimateDialog;

#endif
