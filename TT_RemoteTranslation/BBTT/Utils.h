#pragma once

#define CHECK_ret(x) {if ((ret = (x)) == EXIT_FAILURE) return EXIT_FAILURE;}
#define CHECK_ret_bool(x) {if (!(x)) return EXIT_FAILURE;}
#define CHECK_ret_goto(x) {if ((ret = (x)) == EXIT_FAILURE) goto error_usage;}
