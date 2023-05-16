#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#pragma once

int encode_file(const char *in_file_name, const char *out_file_name);
int decode_file(const char *in_file_name, const char *out_file_name);
