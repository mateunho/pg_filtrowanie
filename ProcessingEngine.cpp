#include "ProcessingEngine.hpp"


ProcessingEngine::ProcessingEngine()
{
}


void ProcessingEngine::Filter2D(cv::Mat _in, cv::Mat &_out, cv::Mat _filter) const
{
    cv::filter2D(_in, _out, -1, _filter);
}
