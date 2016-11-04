/*
 * curl_wrapper.hpp
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CURL_WRAPPER_H 
#define CURL_WRAPPER_H 

#include <json.hpp>

std::string parameters_map_to_parameters_string(
		const std::map<std::string, std::string> &parameters);

struct response_buffer {
	char *memory;
	size_t size;
};
 
static size_t curl_block_callback(
		void *contents, size_t size, size_t nmemb, void *userp);
nlohmann::json get_json_for(
		const std::string &url,
		const std::map<std::string, std::string> &parameters);

#endif /* !SERVER_H */

