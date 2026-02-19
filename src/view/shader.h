#pragma once
#include "../config.h"

unsigned int make_module(const string& filepath, unsigned int module_type);

unsigned int make_shader(const string& vertex_filepath, const string& fragment_filepath);