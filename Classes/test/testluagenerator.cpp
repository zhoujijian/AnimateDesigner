#include <assert.h>
#include "luagenerator.h"

void test_read_write_solution() {
	CoConfig solution;
	solution.path = ".\\test\\solution.lua";
	bool isok = LuaGenerator::generator()->write_solution(solution);
	assert(isok);
	CoConfig saved;
	isok = LuaGenerator::generator()->read_solution(".\\test\\solution.lua", saved);
	assert(isok);
	assert(solution.path.compare(saved.path) == 0);

	CoConfig *filea = new CoConfig(CoKind::Filer, "\\abc\\a.lua");
	CoConfig *fileb = new CoConfig(CoKind::Filer, "\\abc\\b.lua");
	CoConfig *filec = new CoConfig(CoKind::Filer, "\\abc\\c.lua");
	CoConfig *filed = new CoConfig(CoKind::Filer, "\\abc\\d.lua");
	CoConfig *poj0 = new CoConfig(CoKind::Project, ".\\test\\poj0.lua");
	CoConfig *poj1 = new CoConfig(CoKind::Project, ".\\test\\poj1.lua");
	poj0->files.push_back(filea);
	poj1->files.push_back(fileb);
	poj1->files.push_back(filec);
	poj1->files.push_back(filed);

	solution.folders.push_back(poj0);
	solution.folders.push_back(poj1);

	isok = LuaGenerator::generator()->write_solution(solution);
	assert(isok);

	isok = LuaGenerator::generator()->read_solution(".\\test\\solution.lua", saved);
	assert(isok);
	assert(saved.folders.size() == 2);
	assert(saved.folders[0]->kind == CoKind::Project);
	assert(saved.folders[0]->path.compare(poj0->path) == 0);
	assert(saved.folders[0]->files.size() == 1);
	assert(saved.folders[0]->files[0]->kind == CoKind::Filer);
	assert(saved.folders[0]->files[0]->path.compare(filea->path) == 0);

	assert(saved.folders[1]->kind == CoKind::Project);
	assert(saved.folders[1]->path.compare(poj1->path) == 0);	
	assert(saved.folders[1]->files.size() == 3);
	assert(saved.folders[1]->files[0]->kind == CoKind::Filer);
	assert(saved.folders[1]->files[0]->path.compare(fileb->path) == 0);
	assert(saved.folders[1]->files[1]->kind == CoKind::Filer);
	assert(saved.folders[1]->files[1]->path.compare(filec->path) == 0);
	assert(saved.folders[1]->files[2]->kind == CoKind::Filer);
	assert(saved.folders[1]->files[2]->path.compare(filed->path) == 0);
}

void test_read_write_project() {
	CoConfig project;
	project.path = ".\\test\\project.lua";

	bool isok = LuaGenerator::generator()->write_project(project);
	assert(isok);
	CoConfig *saved = LuaGenerator::generator()->read_project(".\\test\\project.lua");
	assert(saved != NULL);
	assert(saved->path == ".\\test\\project.lua");

	CoConfig *file0 = new CoConfig();
	CoConfig *file1 = new CoConfig();
	file0->path = "\\abc\\animate.lua";
	file1->path = "\\abc\\def\\ok.png";
	project.files.push_back(file0);
	project.files.push_back(file1);
	isok = LuaGenerator::generator()->write_project(project);

	saved = LuaGenerator::generator()->read_project(".\\test\\project.lua");
	assert(saved != NULL);
	assert(saved->path == ".\\test\\project.lua");
	assert(saved->files.size() == 2);
	assert(saved->files[0]->kind == CoKind::Filer);
	assert(saved->files[1]->kind == CoKind::Filer);
	assert(file0->path.compare(saved->files[0]->path) == 0);
	assert(file1->path.compare(saved->files[1]->path) == 0);
}

void test_lua_generator() {
	test_read_write_project();
	test_read_write_solution();
}