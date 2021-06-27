#include <iostream>
#include <string>
#include "spdlog/spdlog.h"

#ifndef suffix
#define suffix(msg)  std::string("[func: ")\
        .append(__func__)\
        .append("] [line:").append(std::to_string(__LINE__))\
        .append("] ").append(std::string(msg)).c_str()
#endif


#define LOG_TRACE(...)  Logger::getInstance()->getConsoleLogger()->trace(__VA_ARGS__);\
		                Logger::getInstance()->getFileLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) 	Logger::getInstance()->getConsoleLogger()->debug(__VA_ARGS__);\
						Logger::getInstance()->getFileLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)  	Logger::getInstance()->getConsoleLogger()->info(__VA_ARGS__);\
						Logger::getInstance()->getFileLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)  	Logger::getInstance()->getConsoleLogger()->warn(__VA_ARGS__);\
						Logger::getInstance()->getFileLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) 	Logger::getInstance()->getConsoleLogger()->error( __VA_ARGS__);\
						Logger::getInstance()->getFileLogger()->error(__VA_ARGS__)

static std::string m_logger_file="log.log";

void setLogFile(const std::string file_name="log.log",const std::string file_path="."){
	m_logger_file=file_path+"/"+file_name;
}

class Logger
{
public:
	static Logger* getInstance(){
		static Logger logger;
		return &logger;
	}
	
	std::shared_ptr<spdlog::logger> getConsoleLogger() const{
		return m_console_logger;
	}
	std::shared_ptr<spdlog::logger> getFileLogger() const{
		return m_file_logger;
	}
private:
	// make constructor private to avoid outside instance
	Logger()
	{	
		try
		{
			m_console_logger = spdlog::stdout_color_st("console");
			m_file_logger = spdlog::basic_logger_mt("logger", m_logger_file);
			setLogLevel("info");
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}

	// void initInstance(const std::string m_logger_path="log.log")
 
	~Logger()
	{
		spdlog::drop_all(); // must do this
	}

	void setLogLevel(const std::string& level){
		if (level == "trace")
		{
			m_file_logger->set_level(spdlog::level::trace);
			m_console_logger->flush_on(spdlog::level::trace);
		}
		else if (level == "debug")
		{
			m_file_logger->set_level(spdlog::level::debug);
			m_console_logger->flush_on(spdlog::level::debug);
		}
		else if (level == "info")
		{
			m_file_logger->set_level(spdlog::level::info);
			m_console_logger->flush_on(spdlog::level::info);
		}
		else if (level == "warn")
		{
			m_file_logger->set_level(spdlog::level::warn);
			m_console_logger->flush_on(spdlog::level::warn);
		}
		else if (level == "error")
		{
			m_file_logger->set_level(spdlog::level::err);
			m_console_logger->flush_on(spdlog::level::err);
		}
	}

	void setLogPattern(const std::string& pattern){
		// m_file_logger->set_pattern("%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] [%#] %v"); // with timestamp, thread_id, filename and line number
		m_file_logger->set_pattern(pattern);
	}
    
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
private:
	std::shared_ptr<spdlog::logger> m_file_logger;
	std::shared_ptr<spdlog::logger> m_console_logger;
};