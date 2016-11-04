/*
 * curl_wrapper.hpp
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CURL_WRAPPER_HPP
#define CURL_WRAPPER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

#include <curl/curl.h>

#include "curl_wrapper.hpp"

std::string parameters_map_to_parameters_string(
		const std::map<std::string, std::string> &parameters){
	std::string param_string;
	for (auto &kvpair : parameters) {
		param_string += kvpair.first;
		param_string += "=";
		param_string += kvpair.second;
		param_string += "&";
	}
	return param_string;
}
 
static size_t
curl_block_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct response_buffer *mem = (struct response_buffer *)userp;
 
	mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if(mem->memory == NULL) {
		/* out of memory! */ 
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}
 
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
 
	return realsize;
}
 
nlohmann::json get_json_for(
		const std::string &url,
		const std::map<std::string, std::string> &parameters) {
	CURL *curl_handle;
	CURLcode res;
 
	struct response_buffer chunk;
 
	chunk.memory = (char*)malloc(1); // will be grown as needed by the realloc
									 //above 
	chunk.size = 0;	//no data at this point
 
	//must call before any use of curl
	curl_global_init(CURL_GLOBAL_ALL);
 
	//create a curl object
	curl_handle = curl_easy_init();
 
	// set URL
	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
 
	auto post_data = parameters_map_to_parameters_string(parameters);

	// set the post data
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, post_data.size());
 
	// Set up the call back function
	// pass in a pointer to the data
	curl_easy_setopt(
			curl_handle,
			CURLOPT_POSTFIELDS,post_data.c_str());

	// send all data to curl_block_callback
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, curl_block_callback);
 
	// we pass our 'chunk' struct to the callback function
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
	//go get the json!
	res = curl_easy_perform(curl_handle);

	nlohmann::json return_json;

	// check for errors
	if(res != CURLE_OK) {
		//TODO real error checking
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(res));
	}
	else {
		/*
		 * Now, our chunk.memory points to a memory block that is chunk.size
		 * bytes big and contains the remote file.
		 *
		 * Do something nice with it!
		 */ 
 		return_json = nlohmann::json::parse(
				std::string(chunk.memory, chunk.size));
				printf("%lu bytes retrieved\n", (long)chunk.size);
	}

	/* cleanup curl stuff */ 
	curl_easy_cleanup(curl_handle);
 
	free(chunk.memory);
 
	/* we're done with libcurl, so clean it up */ 
	curl_global_cleanup();
	
	std::string(chunk.memory, chunk.size);
 
	return return_json;
}


#endif /* !CURL_WRAPPER_HPP */
