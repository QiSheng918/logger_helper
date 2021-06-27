#include <iostream>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define LOG_TRACE(...) 	SPDLOG_LOGGER_TRACE(Logger::getInstance()->getConsoleLogger(),__VA_ARGS__);\
		                SPDLOG_LOGGER_TRACE(Logger::getInstance()->getFileLogger(),__VA_ARGS__)
#define LOG_DEBUG(...) 	SPDLOG_LOGGER_DEBUG(Logger::getInstance()->getConsoleLogger(),__VA_ARGS__);\
						SPDLOG_LOGGER_DEBUG(Logger::getInstance()->getFileLogger(),__VA_ARGS__)
#define LOG_INFO(...)  	SPDLOG_LOGGER_INFO(Logger::getInstance()->getConsoleLogger(),__VA_ARGS__);\
						SPDLOG_LOGGER_INFO(Logger::getInstance()->getFileLogger(),__VA_ARGS__)
#define LOG_WARN(...)  	SPDLOG_LOGGER_WARN(Logger::getInstance()->getConsoleLogger(),__VA_ARGS__);\
						SPDLOG_LOGGER_WARN(Logger::getInstance()->getFileLogger(),__VA_ARGS__)
#define LOG_ERROR(...) 	SPDLOG_LOGGER_ERROR(Logger::getInstance()->getConsoleLogger(),__VA_ARGS__);\
						SPDLOG_LOGGER_ERROR(Logger::getInstance()->getFileLogger(),__VA_ARGS__)

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
			std::string pattern="[%Y-%m-%d %H:%M:%S.%f] [%^file %s] [func %!] [line %#] [%l]  %v";
			setLogPattern(pattern);
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

	void setLogPattern(const std::string& pattern=""){
		spdlog::set_pattern(pattern);
		// m_file_logger->set_pattern("%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] [%#] %v"); // with timestamp, thread_id, filename and line number
		// m_file_logger->set_pattern(pattern);
	}
    
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
private:
	std::shared_ptr<spdlog::logger> m_file_logger;
	std::shared_ptr<spdlog::logger> m_console_logger;
};