#pragma once
#ifndef CONFIG_H
#include <map>
#include <string>

std::map<std::string, RGB> G_color_map = {
	{"green", RGB(57, 255, 20)},
	{"red", RGB(255, 51, 51)},
	{"gold", RGB(255, 255, 51)},
	{"purple", RGB(204, 153, 255)}
};

std::string G_color_dict_key[] = { "green", "red", "gold", "purple" };

int G_color_rotation = 0;

#endif // !CONFIG_H
