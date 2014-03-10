#include <stack>
#include <string>
#include "luagenerator.h"
#include "cocos2d.h"
#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"
#include "LuaCocos2d.h"

using namespace cocos2d;
using namespace std;

LuaGenerator* LuaGenerator::instance = NULL;

LuaGenerator* LuaGenerator::generator() {
	if (!instance) {
		instance = new LuaGenerator();
	}
	return instance;
}

bool LuaGenerator::init() {
	CCLuaEngine *E = CCLuaEngine::defaultEngine();	
    CCScriptEngineManager::sharedManager()->setScriptEngine(E);
	L = E->getLuaState();

	string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("lua/animat.lua");
	int r = luaL_dofile(L, path.c_str());
	if (r != 0) {
		CCLog("[LuaLoader Error]Load system file [animat.lua] fail, %s!", lua_tostring(L, -1));
		lua_pop(L, 1);
		CCAssert(false, "Load animat.lua file error!");	
		return false;
	}
    E->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());

	return true;
}

bool LuaGenerator::open_lua_script() {
	const char *poj_path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("lua/project.lua");
	int r = luaL_dofile(L, poj_path);
	if (r != 0) {
		CCLog("[LuaLoader Warning]No project file specified or load error! Lua Hint %s!", lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	const char *frame_path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("lua/animate_frame.lua");
	r = luaL_dofile(L, frame_path);
	if (r != 0) {
		CCLog("[LuaLoader Error or Warning]No animate-frame file specified or load error!"
		      "Make sure you are not to open animation! Lua Hint %s!", lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	return true;
}

bool LuaGenerator::read_solution(const char *path, CoConfig& solution) {
	int r = luaL_dofile(L, path);
	if (r != 0) {
		CCLog("LuaLoader Error]read solution file %s error %s!", path, lua_tostring(L, -1));
		lua_pop(L, 1);
		return false;
	}

	if (!lua_istable(L, -1)) {
		CCLog("[LuaLoader Error]read solution file %s, no solution table return!", path);
		return false;
	}

	// solution table on stack
	{
		solution.path = path;
		for (int i = 1; i <= luaL_getn(L, -1); ++ i) {
			lua_rawgeti(L, -1, i);
			if (!lua_isstring(L, -1)) {
				CCLog("LuaLoader Error]read solution %s format error, project %d path not string!", path, i);
			} else {
				CoConfig *poj = read_project(lua_tostring(L, -1));
				solution.folders.push_back(poj);
				lua_pop(L, 1);
			}
		}
	}
	lua_pop(L, 1);

	return true;
}

CoConfig* LuaGenerator::read_folder() {
	CoConfig *config = new CoConfig();
	config->kind = CoKind::Folder;

	lua_pushstring(L, "alias");
	lua_gettable(L, -2);
	luaL_checktype(L, -1, LUA_TSTRING);
	config->alias = lua_tostring(L, -1);
	lua_pop(L, 1);

	read_file(config);

	lua_pushstring(L, "folders");
	lua_gettable(L, -2);
	{
		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);
			return config;
		}

		for (int i = 0; i < luaL_getn(L, -1); ++ i) {
			CoConfig *folder = read_folder();
			if (folder) {
				config->folders.push_back(folder);
			}
		}		
	}
	lua_pop(L, 1);
	return config;
}

void LuaGenerator::read_file(CoConfig *config) {
	lua_pushstring(L, "files");
	lua_gettable(L, -2);
	{
		if (!lua_isnil(L, -1)) {
			for (int i = 1; i <= luaL_getn(L, -1); ++ i) {
				lua_rawgeti(L, -1, i);
				luaL_checktype(L, -1, LUA_TSTRING);
				if (lua_isstring(L, -1)) {
					CoConfig *file = new CoConfig(CoKind::Filer, lua_tostring(L, -1));
					file->alias = file->path.substr(file->path.find_last_of("\\"));
					config->files.push_back(file);

					lua_pop(L, 1);
				}
			}
		}
	}
	lua_pop(L, 1);
}

CoConfig* LuaGenerator::read_project(const char *path) {
	int r = luaL_dofile(L, path);
	if (r) {
		CCLog("[LuaLoader Error]read project file %s error %s!", path, lua_tostring(L, -1));
		lua_pop(L, 1);
		return NULL;
	}

	if (!lua_istable(L, -1)) {
		CCLog("[LuaLoader Error]read project file %s, no project table return!", path);
		return NULL;
	}

	// stack top is project table	
		CoConfig *project = read_folder();
		project->kind = CoKind::Project;
		project->path = path;	
	lua_pop(L, 1);

	return project;
}

bool LuaGenerator::write_solution(const CoConfig& solution) {
	lua_getglobal(L, "save_solution");

	lua_pushstring(L, solution.path.c_str());
	lua_newtable(L);
	for (int i = 0; i < solution.folders.size(); ++ i) {
		CoConfig *poj = solution.folders.at(i);
		lua_pushstring(L, poj->path.c_str());
		lua_rawseti(L, -2, i + 1);
	}

	if (lua_pcall(L, 2, 0, 0)) {
		CCLog("[LuaLoader Error]write solution file to path %s error %s!", solution.path.c_str(), lua_tostring(L, -1));
		lua_pop(L, 1);
		return false;
	}

	for (int i = 0; i < solution.folders.size(); ++ i) {
		CoConfig *poj = solution.folders.at(i);
		if (!write_project(*poj)) { return false; }
	}
	return true;
}

void LuaGenerator::write_folder(const CoConfig *folder) {
	lua_newtable(L);
	{
		lua_pushstring(L, "alias");
		lua_pushstring(L, folder->alias.c_str());
		lua_settable(L, -3);

		lua_pushstring(L, "files");
		lua_newtable(L);
		{
			for (int i = 0; i < folder->files.size(); ++ i) {
				CoConfig *file = folder->files.at(i);
				lua_pushstring(L, file->path.c_str());
				lua_rawseti(L, -2, i + 1);
			}
		}
		lua_settable(L, -3);

		if (folder->folders.size() > 0) {
			lua_pushstring(L, "folders");
			lua_newtable(L);
			{
				for (int i = 0; i < folder->folders.size(); ++ i) {
					CoConfig *folder = folder->folders.at(i);
					write_folder(folder);
					lua_rawseti(L, -2, i + 1);
				}
			}
			lua_settable(L, -3);
		}
	}
}

bool LuaGenerator::write_project(const CoConfig& project) {
	lua_getglobal(L, "save_project");

	lua_pushstring(L, project.path.c_str());
	write_folder(&project);

	if (lua_pcall(L, 2, 0, 0)) {
		CCLog("[LuaLoader Error]write project file to path %s error %s!", project.path.c_str(), lua_tostring(L, -1));
		lua_pop(L, 1);
		return false;
	}
	return true;
}

void LuaGenerator::close_lua_script() {
	if (NULL != L) {
		lua_close(L);
	}
}

#define push_num_attr(name, var) lua_pushstring(L, name); lua_pushnumber(L, var); lua_settable(L, -3);
#define  pop_num_attr(name, var) lua_pushstring(L, name); lua_gettable(L, -2);    var = lua_tonumber(L, -1); lua_pop(L, 1);

void LuaGenerator::generat_png_infor(const LuaPngInfo *png_info, int png_count) {
	lua_newtable(L);
	for (int i = 0; i < png_count; ++ i) {
		lua_pushnumber(L, i);

		lua_newtable(L);
		{
			push_num_attr("pngid", png_info[i].pngid);
			push_num_attr("rect_count", png_info[i].rect_count);

			lua_pushstring(L, "png_path");
			lua_pushstring(L, png_info[i].png_path);
			lua_settable(L, -3);

			lua_pushstring(L, "rects");
			lua_newtable(L);
			{
				for (int k = 0; k < png_info[i].rect_count; ++ k) {
					lua_pushnumber(L, k);
					lua_newtable(L);
					{
						push_num_attr("rectid", png_info[i].png_rect[k].rectid);
						push_num_attr("x", png_info[i].png_rect[k].x);
						push_num_attr("y", png_info[i].png_rect[k].y);
						push_num_attr("w", png_info[i].png_rect[k].width);
						push_num_attr("h", png_info[i].png_rect[k].height);
					}
					lua_settable(L, -3);
				}
			}
			lua_settable(L, -3);
		}
		lua_settable(L, -3);
	}
	lua_setglobal(L, "pngres");
}

void LuaGenerator::read_png_path(vector<string>& png_path) {
	lua_getglobal(L, "png");
	if (lua_isnil(L, -1) || !lua_istable(L, -1)) {
		lua_pop(L, 1);
		CCLog("[Read PNG path Error]png variable should be a table!");
		return;
	}
	int png_count = luaL_getn(L, -1);
	for (int i = 1; i <= png_count; i ++) {
		lua_rawgeti(L, -1, i);
		luaL_checktype(L, -1, LUA_TSTRING);
		png_path.push_back(lua_tostring(L, -1));
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
}

int LuaGenerator::read_frame_infor(LuaKeySprite *key_sprite, int sprite_count, float& basex, float& basey) {
	CCLog("Read animate-frame information ==================\n");

	lua_getglobal(L, "animate_frame");
	if (lua_isnil(L, -1) || !lua_istable(L, -1)) {
		CCLog("Read global animat-frame error!");
		lua_pop(L, 1);
		return 0;
	}

	int key_sprite_count;

	pop_num_attr("basex", basex);
	pop_num_attr("basey", basey);
	pop_num_attr("sprite_count", key_sprite_count);

	int m;
	string space;
#define INDENT(n) \
	space.clear(); \
	for (m = 0; m < n; ++ m) { space.append(" "); }

	INDENT(0);
	CCLog("basex %f, basey %f, sprite count %d\n", basex, basey, key_sprite_count);

	for (int i = 0; i < key_sprite_count; ++ i) {
		lua_pushnumber(L, i);
		lua_gettable(L, -2); {
			lua_pushstring(L, "frame_count");
			lua_gettable(L, -2);
			key_sprite[i].key_frame_count = (int)lua_tonumber(L, -1);
			lua_pop(L, 1);

			INDENT(4);
			CCLog("%ssprite %d, key frame count %d:\n", space.c_str(), i, key_sprite[i].key_frame_count);

			for (int k = 0; k < key_sprite[i].key_frame_count; ++ k) {
				lua_pushnumber(L, k);
				lua_gettable(L, -2); {
					LuaFrameAttribute& attr = key_sprite[i].key_frame_attribute[k];
					pop_num_attr("id",   attr.key_frame_id);
					pop_num_attr("posx", attr.posx);
					pop_num_attr("posy", attr.posy);
					pop_num_attr("scax", attr.scalex);
					pop_num_attr("scay", attr.scaley);
					pop_num_attr("rota", attr.rotate);

					INDENT(8);
					CCLog("%sframe-id %d, posx %f, posy %f, scax %f, scay %f, rota %f\n",
					      space.c_str(),
					      attr.key_frame_id,
					      attr.posx, attr.posy,
					      attr.scalex, attr.scaley,
					      attr.rotate);
					
					lua_pushstring(L, "rect");
					lua_gettable(L, -2); {
						LuaRectSpriteFrame& frame = attr.rect_sprite_frame;
						pop_num_attr("orix", frame.orix);
						pop_num_attr("oriy", frame.oriy);
						pop_num_attr("widt", frame.width);
						pop_num_attr("heig", frame.heigt);

						lua_pushstring(L, "path");
						lua_gettable(L, -2);
						strcpy(frame.png_path, lua_tostring(L, -1));
						lua_pop(L, 1);

						INDENT(12);
						CCLog("%sFrame rect orix %f, oriy %f, width %f, height %f, path %s\n",
						      space.c_str(),
						      frame.orix,
						      frame.oriy,
						      frame.width,
						      frame.heigt,
						      frame.png_path);
					}
					lua_pop(L, 1);
				}
				lua_pop(L, 1);
			}
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	return key_sprite_count;
}

void LuaGenerator::generat_frame_infor(const LuaKeySprite *key_sprite, int sprite_count, float basex, float basey) {
	lua_newtable(L);

	push_num_attr("basex", basex);
	push_num_attr("basey", basey);
	push_num_attr("sprite_count", sprite_count);

	for (int i = 0; i < sprite_count; ++ i) {
		lua_pushnumber(L, i);
		lua_newtable(L); {
			push_num_attr("frame_count", key_sprite[i].key_frame_count);

			for (int k = 0; k < key_sprite[i].key_frame_count; ++ k) {
				lua_pushnumber(L, k);
				lua_newtable(L); {
					const LuaFrameAttribute& attr = key_sprite[i].key_frame_attribute[k];

					push_num_attr("posx", attr.posx);
					push_num_attr("posy", attr.posy);
					push_num_attr("scax", attr.scalex);
					push_num_attr("scay", attr.scaley);
					push_num_attr("rota", attr.rotate);
					push_num_attr("id",   attr.key_frame_id);

					lua_pushstring(L, "rect");
					lua_newtable(L); {
						const LuaRectSpriteFrame& frame = attr.rect_sprite_frame;

						push_num_attr("orix", frame.orix);
						push_num_attr("oriy", frame.oriy);
						push_num_attr("widt", frame.width);
						push_num_attr("heig", frame.heigt);

						lua_pushstring(L, "path");
						lua_pushstring(L, frame.png_path);
						lua_settable(L, -3);
					}
					lua_settable(L, -3);
				}
				lua_settable(L, -3);
			}
		}
		lua_settable(L, -3);
	}
	lua_setglobal(L, "animate_frame");
}

int LuaGenerator::read_png_infor(LuaPngInfo *png_info, int png_count) {
	return 0;
}

void LuaGenerator::save_generat() {
	lua_getglobal(L, "save_animate");
	int r = lua_pcall(L, 0, 0, 0);
	if (r != 0) {
		CCLog("[LuaGenerator Error]execute save-animate failure: %s", lua_tostring(L, -1));
		lua_pop(L, 1);
	}
}
