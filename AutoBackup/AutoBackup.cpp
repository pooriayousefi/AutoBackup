
/***************************************************************************************/
/*                                                                                     */
/*                                    Auto-Backup                                      */
/*                                                                                     */
/*                                   Pooria Yousefi                                    */
/*                                pooriayousefi@aol.com                                */
/*                      https://www.linkedin.com/in/pooriayousefi/                     */
/*                                       2022                                          */
/*                                                                                     */
/***************************************************************************************/

#include "AutoBackup.h"

// entry point
int main()
{
	try
	{
		// variables...
		auto period{ 0i64 };
		std::string tmp_path{};
		std::filesystem::path src_path{};
		auto dst_paths_size{ 0U };
		std::vector<std::filesystem::path> dst_paths{};

		// input reading...
		std::cout << "\n\nEnter the source path: "; std::cin >> tmp_path;
		src_path = tmp_path;
		std::cout << "\n\nEnter the number of destination paths: "; std::cin >> dst_paths_size;
		dst_paths.reserve(dst_paths_size);
		std::cout << "\n\nEnter the destination paths:\n";
		for (auto i{ 0U }; i < dst_paths_size; ++i)
		{
			std::cin >> tmp_path;
			dst_paths.emplace_back(tmp_path);
		}
		std::cout << "\n\nEnter the backup period in seconds: "; std::cin >> period;

		while (1)
		{
			auto ti = std::chrono::steady_clock::time_point::clock::now();
			auto tf = ti;
			do
			{
				tf = std::chrono::steady_clock::time_point::clock::now();
			} while (std::chrono::duration<double>(tf - ti).count() <= period);
			for (auto& dst_path : dst_paths)
			{
				std::filesystem::copy(
					src_path,
					dst_path,
					std::filesystem::copy_options::copy_symlinks |
					std::filesystem::copy_options::overwrite_existing |
					std::filesystem::copy_options::recursive
				);
				auto now_time = std::chrono::system_clock::now();
				auto now_time_t = std::chrono::system_clock::to_time_t(now_time);
				std::cout
					<< "\n\n---------------------------------------------------------\n"
					<< "\n last backup: " << ctime(&now_time_t);
			}
		}

		return 0;
	}
	catch (const std::exception& xxx)
	{
		std::cerr << xxx.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "UNCAUGHT EXCEPTION DETECTED\n";
		return 1;
	}
}
