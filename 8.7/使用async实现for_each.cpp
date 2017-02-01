#include <thread>
#include <future>

template<typename Iterator,typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
	unsigned long const length = std::distance(first, last);
	if (!length)
		return;
	unsigned long const min_per_thread = 25;

	if (length < (2 * min_per_thread))
		std::for_each(first, last, f);//1
	else
	{
		Iterator const mid_point = first + length / 2;
		std::future<void> first_half =
			std::async(&parallel_for_each<Iterator, Func>,
				first, mid_point, f);	//2
		parallel_for_each(mid_point, last, f);//3
		first_half.get();//4
	}
}