#ifndef UTIL_TESTUTILS_H_
#define UTIL_TESTUTILS_H_

/**
 * Helper class that provides methods for performing tests.
 */
class TestUtils {
public:
	
	/**
	 * Checks whether the file found at the given TEST_OUTPUT_FILE path matches the given ASSUMED_CONTENT.
	 * Reads the file found at the given path and compares line for line with the elements of the ASSUMED_CONTET array.
	 * Returns 0 if everything matches.
	 * Returns -1 if a mismatch occured.
	 */
	static inline int checkOutput(const std::string ASSUMED_CONTENT[], const int ASSUMED_CONTENT_LENGTH, const char* TEST_OUTPUT_FILE) {
		// Read file
		std::ifstream ifile(TEST_OUTPUT_FILE);
		std::string strLine;

		//compare line for line
		int i = 0;
		bool matches = true;
		std::string wholeText;
		while (std::getline(ifile, strLine) && i<ASSUMED_CONTENT_LENGTH) {
			wholeText += strLine;
			if (ASSUMED_CONTENT[i].compare(strLine) != 0){
				std::fprintf(stderr, "Mismatch \n'%s' (assumed) \nvs \n'%s' (read)\n", ASSUMED_CONTENT[i].c_str(), strLine.c_str());
				matches = false;
				break;
			}
			i++;
		}

		if (matches) {
			// Delete file again
			std::remove(TEST_OUTPUT_FILE);
			return 0;
		}
		else {
			std::string assumedText;
			for (int i = 0; i < ASSUMED_CONTENT_LENGTH; i++){
				assumedText += ASSUMED_CONTENT[i];
			}
			std::fprintf(stderr, "Mismatch between written and assumed file content\nAssumed:\n%s\n\nActual:\n%s\n", assumedText.c_str(), wholeText.c_str());
			return -1;
		}
	}
};

#endif /* UTIL_TESTUTILS_H_ */
