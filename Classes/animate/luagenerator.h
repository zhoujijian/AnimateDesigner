#ifndef _LUA_GENERATOR_H_
#define _LUA_GENERATOR_H_

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <vector>
#include <string>
#include "animatcommon.h"

class ILuaGenerator {
public:
	virtual ~ILuaGenerator() { }

	virtual bool open_lua_script() { return false; }
	virtual void close_lua_script() { }
	virtual void read_png_path(std::vector<std::string>& png_path) { }
	virtual void generat_png_infor(const LuaPngInfo *png_info, int png_count) { }
	virtual void generat_frame_infor(const LuaKeySprite *key_sprite, int sprite_count, float basex, float basey) { }
	virtual int  read_frame_infor(LuaKeySprite *key_sprite, int sprite_count, float& basex, float& basey) { return 0; }
	virtual int  read_png_infor(LuaPngInfo *png_info, int png_count) { return NULL; }

	virtual void save_generat() { }
};

class LuaGenerator : public ILuaGenerator {
private:
	LuaGenerator() : L(NULL) {
		init();
	}

public:
	~LuaGenerator() { }

	static LuaGenerator* generator();

	virtual bool open_lua_script();
	virtual void close_lua_script();
	virtual void read_png_path(std::vector<std::string>& png_path);
	virtual void generat_png_infor(const LuaPngInfo *png_info, int png_count);
	virtual void generat_frame_infor(const LuaKeySprite *key_sprite, int sprite_count, float basex, float basey);
	virtual int  read_frame_infor(LuaKeySprite *key_sprite, int sprite_count, float& basex, float& basey);

	virtual int  read_png_infor(LuaPngInfo *png_info, int png_count);
	virtual void save_generat();

	bool read_solution(const char *path, CoConfig& solution);
	CoConfig* read_project (const char *path);
	bool write_solution(const CoConfig& solution);
	bool write_project (const CoConfig& project);

protected:
	virtual bool init();

private:	
	CoConfig* read_folder();
	void read_file(CoConfig *config);

	void write_folder(const CoConfig *folder);

private:
	lua_State *L;
	static LuaGenerator *instance;
};

#endif
