/* version 1.1
 * Tue 19 May 2009 09:57:03 PM PDT
 * Dmitri Volper
 */
#ifndef LOGGING_H
#define LOGGING_H
#include <fstream>
#include <cstring>

namespace LOGGING {

	struct LOG_STATISTICS {
		std::string func_name;
		std::string file_name;
		unsigned line;
		std::ostream& os;
		unsigned num_calls;
		double total_time;
		LOG_STATISTICS(
				const std::string & func_name,
				const std::string & file_name,
				int line,
				std::ostream& os
				)
			:
				func_name(func_name),
				file_name(file_name),
				line(line),
				os(os),num_calls(0),total_time(0.0)
		{}
		~LOG_STATISTICS() {
			os << FUNCTION_LOG << " Statistics for " << func_name
				<< "   (" << file_name << " +" << line << ")\n"
				<< FUNCTION_LOG << "      called " << num_calls << " times\n";
			os << FUNCTION_LOG << "      average time " << total_time/num_calls;
			os << std::endl;
		}
		private:
		void operator=(const LOG_STATISTICS&);
		LOG_STATISTICS(const LOG_STATISTICS&);
	};

	class LOG_CLASS {
		std::string func_name;
		std::string file_name;
		std::ostream& os;
		ticks start;
		LOG_STATISTICS & log_stats;
		const bool enter_leave;
		public:
		LOG_CLASS(
				const std::string & func_name,
				const std::string & file_name,
				unsigned line,
				std::ostream& os,LOG_STATISTICS & log_stats,
				const bool enter_leave = true)
			:
				func_name(func_name),
				file_name(file_name),
				os(os),
				log_stats(log_stats),
				enter_leave(enter_leave)
		{
			if (enter_leave) //since enter_leave is a constant, "if" will be optimized away
				os << FUNCTION_LOG << " entering " << func_name << " (" << file_name
					<< " +" << line << ")" << std::endl;
			start = getticks();
		}
		~LOG_CLASS() {
			ticks stop = getticks();
			double duration = elapsed(stop,start);
			if (enter_leave) //since enter_leave is a constant, "if" will be optimized away
				os << FUNCTION_LOG << " leaving " << func_name << " (" << file_name
					<< ") " << duration << std::endl;

			++(log_stats.num_calls);
			log_stats.total_time += duration;
		}
		private:
		LOG_CLASS(const LOG_CLASS&);
		void operator=(const LOG_CLASS);
	};
}
#endif
