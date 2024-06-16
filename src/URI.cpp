#include "URI.hpp"

namespace libutils {

	URIView& URIView::operator=(const etl::string_view& url) {
		mValid = false;
		if (url.length() > etl::numeric_limits<uint16_t>::max()) return *this;
		const uint16_t url_length = static_cast<uint16_t>(url.length());
		mBufferSource = url;
		mPort = 0;
		uint16_t start_position = 0;
		ParseType parse_type = ParseType::SCHEME;
		for (uint16_t i = 0; i < url_length; i++) {
			switch (parse_type) {
			case ParseType::SCHEME: {
				if (url[i] == ':') {
					mScheme = etl::string_view(&url[start_position], i - start_position);
					i++;
					for (; i < url_length; i++) {
						if (url[i] != '/') {
							start_position = i;
							i--;
							parse_type = ParseType::USERNAME;
							break;
						}
					}
				}
			}
								  break;
			case ParseType::USERNAME: {
				if (url[i] == ':') {
					mUsername = etl::string_view(&url[start_position], i - start_position);
					start_position = i + 1;
					parse_type = ParseType::PASSWORD;
				}
				else if (url[i] == '@') {
					mUsername = etl::string_view(&url[start_position], i - start_position);
					start_position = i + 1;
					parse_type = ParseType::URL;

				}
				else if (url[i] == '/') { // no username, its url
					mUrl = etl::string_view(&url[start_position], i - start_position);
					start_position = i;
					i--;
					parse_type = ParseType::PATH;
				}
				else if (i + 1u == url_length) { // no username its url and end
					mUrl = etl::string_view(&url[start_position], i - start_position);
					parse_type = ParseType::END;
				}
			}
									break;
			case ParseType::PASSWORD: {
				if (url[i] == '@') {
					mPassword = etl::string_view(&url[start_position], i - start_position);
					start_position = i + 1;
					parse_type = ParseType::URL;
				}
				else if (url[i] == '/') { // no username, no password, its url and port
					mPort = etl::to_arithmetic<uint16_t>(&url[start_position], i - start_position, 10).value();
					mUrl = mUsername;
					mUsername = nullptr;
					mPassword = nullptr;
					start_position = i;
					i--;
					parse_type = ParseType::PATH;
				}
				else if (i + 1u == url_length) { // no username its url and end
					mPort = etl::to_arithmetic<uint16_t>(&url[start_position], (i + 1u) - start_position, 10).value();
					mUrl = mUsername;
					mUsername = nullptr;
					mPassword = nullptr;
				}
			}
									break;
			case ParseType::URL: {
				if (url[i] == ':' || url[i] == '/' || i + 1u == url_length) {
					if (url[i] == '/') {
						mUrl = etl::string_view(&url[start_position], i - start_position);
						start_position = i;
						i--;
						parse_type = ParseType::PATH;
					}
					else if (url[i] == ':') {
						mUrl = etl::string_view(&url[start_position], i - start_position);
						start_position = i + 1;
						parse_type = ParseType::PORT;
					}
					else {
						mUrl = etl::string_view(&url[start_position], i + 1u - start_position);
					}
				}
			}
							   break;
			case ParseType::PORT: {
				if (i + 1u == url_length || url[i] == '/') {
					mPort = etl::to_arithmetic<uint16_t>(&url[start_position], (url[i] == '/' ? i : i + 1u) - start_position, 10).value();
					if (url[i] == '/') {
						start_position = i;
						i--;
						parse_type = ParseType::PATH;
						continue;
					}
				}
				else if (!std::isdigit(url[i])) {
					return *this;
				}
			}
								break;
			case ParseType::PATH: {
				mPath = etl::string_view(&url[start_position], (i + 1u) - start_position);
			}
								break;
			case ParseType::END: break;
			}
		}
		if (mScheme.length() > 0 && mUrl.length() > 0) {
			mValid = true;
		}
		return *this;
	}
}