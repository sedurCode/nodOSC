#include <armaFilter.h>
#include <math.h>

bool ArmaFilter::setup(float tau, float fs)
{
    this->stateMAz1 = 0.0f;
    this->stateMAz2 = 0.0f;
    this->tau = tau;
    float pi = 3.141592;
    float fc = 1.0f / (2.0f * pi * (tau / 1000.0f));
    this->alpha = exp(-2 * pi * fc / fs); //decayfactor
    this->oneMinusAlpha = 1 - alpha; //amplitudefactor
    //this->alpha = 0.0f;
    //this->oneMinusAlpha = 0.0f;
    return true;
}

bool ArmaFilter::reset()
{
    this->stateMAz1 = 0.0f;
    this->stateMAz2 = 0.0f;

    return true;
}

float ArmaFilter::process(float x)
{
    float accumulator = x * x;
    accumulator = this->oneMinusAlpha * accumulator + this->alpha * this->stateMAz1;
    this->stateMAz1 = accumulator;
    float y = sqrt(accumulator);
    return y;
}
