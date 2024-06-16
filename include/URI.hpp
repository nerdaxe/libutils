#ifndef URI_TPP
#define URI_TPP
#include <cctype>
#include <etl/to_arithmetic.h>
#include <etl/string_view.h>
#include <etl/string.h>
#ifdef max
	#undef max
#endif 
#ifndef LIBUTILS_URI_MAX_BUFFER
	#define LIBUTILS_URI_MAX_BUFFER 256u
#endif

namespace libutils {

	class URIView {
		private:
			enum ParseType : uint8_t {
				SCHEME,
				USERNAME,
				PASSWORD,
				URL,
				PORT,
				PATH,
				END
			};
		public:
			URIView(URIView&& move) = delete;
			URIView(const URIView& copy) = delete;
			URIView(const char* url) : URIView(etl::string_view(url,strlen(url))) {}
			URIView(const etl::string_view& url) { operator=(url); }
			URIView() : mValid(false) {}
			URIView& operator=(const etl::string_view& url);
			
			inline bool Valid() const {
				return mValid;
			}
			inline const etl::string_view& Scheme() const {
				return mScheme;
			}
			inline const etl::string_view& Username() const {
				return mUsername;
			}
			inline const etl::string_view& Password() const {
				return mPassword;
			}
			inline const etl::string_view& Url() const {
				return mUrl;
			}
			inline const etl::string_view& Path() const {
				return mPath;
			}
			inline uint16_t Port() const {
				return mPort;
			}
			inline const etl::string_view& BufferSource() const {
				return mBufferSource;
			}
		private:
			etl::string_view mBufferSource;
			etl::string_view mScheme;
			etl::string_view mUsername;
			etl::string_view mPassword;
			etl::string_view mUrl;
			etl::string_view mPath;
			uint16_t mPort;
			bool mValid;
	};
	class URI {
		public:
			URI(URI&& move) = delete;
			URI(const URI& copy) = delete;
			URI(const char* url) : URI(etl::string_view(url, strlen(url))) {}
			URI(const etl::string_view& url_source) : mBuffer(url_source), mURI(mBuffer) {}	
			URI() {}
			URI& operator=(const etl::string_view& source) {
				mBuffer = etl::string<LIBUTILS_URI_MAX_BUFFER>(source);
				mURI = mBuffer;
				return *this;
			}
			URI& operator=(const URIView& source) {
				//mBuffer(source.BufferSource());
				//mURI = mBuffer;
				mURI = source.BufferSource();
				return *this;
			}
			inline bool Valid() const {
				return mURI.Valid();
			}
			inline const etl::string_view& Scheme() const {
				return mURI.Scheme();
			}
			inline const etl::string_view& Username() const {
				return mURI.Username();
			}
			inline const etl::string_view& Password() const {
				return mURI.Password();
			}
			inline const etl::string_view& Url() const {
				return mURI.Url();
			}
			inline const etl::string_view& Path() const {
				return mURI.Path();
			}
			inline uint16_t Port() const {
				return mURI.Port();
			}
		private:
			etl::string<LIBUTILS_URI_MAX_BUFFER> mBuffer;
			URIView mURI;
	};
}

#endif