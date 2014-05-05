#ifndef PROCESSINGENGINE_HPP
#define PROCESSINGENGINE_HPP


#include <opencv2/imgproc/imgproc.hpp> // cv::Mat, cv::filter2D()


class ProcessingEngine
{
public:
    ProcessingEngine();

    // metoda filtrujaca pierwsza macierz za pomoca trzeciej macierzy zapisujaca wynik do drugiej macierzy
    void Filter2D(cv::Mat _in, cv::Mat &_out, cv::Mat _filter) const;
};

#endif // PROCESSINGENGINE_HPP
