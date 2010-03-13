/*This file is generated by luagen.*/
#include "lua_ftk_font_default.h"
#include "lua_ftk_callbacks.h"

static void tolua_reg_types (lua_State* L)
{
	tolua_usertype(L, "FtkFontDefault");
}

static int lua_ftk_font_default_create(lua_State* L)
{
	tolua_Error err = {0};
	FtkFont* retv;
	char* filename;
	int bold;
	int italic;
	int size;
	int param_ok = tolua_isstring(L, 1, 0, &err) && tolua_isnumber(L, 2, 0, &err) && tolua_isnumber(L, 3, 0, &err) && tolua_isnumber(L, 4, 0, &err);

	return_val_if_fail(param_ok, 0);

	filename = (char*)tolua_tostring(L, 1, 0);
	bold = tolua_tonumber(L, 2, 0);
	italic = tolua_tonumber(L, 3, 0);
	size = tolua_tonumber(L, 4, 0);
	retv = ftk_font_default_create(filename, bold, italic, size);
	tolua_pushusertype(L, (FtkFont*)retv, "FtkFont");

	return 1;
}

int tolua_ftk_font_default_init(lua_State* L)
{
	tolua_open(L);
	tolua_reg_types(L);
	tolua_module(L, NULL, 0);
	tolua_beginmodule(L, NULL);
	tolua_cclass(L,"FtkFontDefault", "FtkFontDefault", "FtkFont", NULL);
	tolua_beginmodule(L, "FtkFontDefault");
	tolua_function(L, "Create", lua_ftk_font_default_create);
	tolua_endmodule(L);
	tolua_endmodule(L);


	return 1;
}
