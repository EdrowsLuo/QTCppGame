//
// Created by admin on 2018/9/15.
//

#ifndef QT_BB_EASING_H
#define QT_BB_EASING_H

#include <algorithm>
#include <vector>
#include <cmath>

// http://easings.net/
namespace edp{
    class easing {
        public:
        static const double PI = 3.1415926535897932384626;
        static const double elastic_const = 2 * 3.1415926535897932384626 / .3;
        static const double elastic_const2 = .3 / 4;

        static const double back_const = 1.70158;
        static const double back_const2 = 1.70158 * 1.525;

        static const double bounce_const = 1 / 2.75;

        static const int
                None = 0,
                Out = 1,
                In = 2,
                InQuad = 3,
                OutQuad = 4,
                InOutQuad = 5,
                InCubic = 6,
                OutCubic = 7,
                InOutCubic = 8,
                InQuart = 9,
                OutQuart = 10,
                InOutQuart = 11,
                InQuint = 12,
                OutQuint = 13,
                InOutQuint = 14,
                InSine = 15,
                OutSine = 16,
                InOutSine = 17,
                InExpo = 18,
                OutExpo = 19,
                InOutExpo = 20,
                InCirc = 21,
                OutCirc = 22,
                InOutCirc = 23,
                InElastic = 24,
                OutElastic = 25,
                OutElasticHalf = 26,
                OutElasticQuarter = 27,
                InOutElastic = 28,
                InBack = 29,
                OutBack = 30,
                InOutBack = 31,
                InBounce = 32,
                OutBounce = 33,
                InOutBounce = 34,
                OutPow10 = 35,
                Jump = 36;

        static double applyEasing(double v, int easing) {
            switch (easing) {
                case None:
                    return v;
                case In:
                case InQuad:
                    return v * v;
                case Out:
                case OutQuad:
                    return v * (2 - v);
                case InOutQuad:
                    if (v < .5) return v * v * 2;
                    return --v * v * -2 + 1;
                case InCubic:
                    return v * v * v;
                case OutCubic:
                    return --v * v * v + 1;
                case InOutCubic:
                    if (v < .5) return v * v * v * 4;
                    return --v * v * v * 4 + 1;

                case InQuart:
                    return v * v * v * v;
                case OutQuart:
                    return 1 - --v * v * v * v;
                case InOutQuart:
                    if (v < .5) return v * v * v * v * 8;
                    return --v * v * v * v * -8 + 1;

                case InQuint:
                    return v * v * v * v * v;
                case OutQuint:
                    return --v * v * v * v * v + 1;
                case InOutQuint:
                    if (v < .5) return v * v * v * v * v * 16;
                    return --v * v * v * v * v * 16 + 1;

                case InSine:
                    return 1 - cos(v * PI * .5);
                case OutSine:
                    return sin(v * PI * .5);
                case InOutSine:
                    return .5 - .5 * cos(PI * v);

                case InExpo:
                    return pow(2, 10 * (v - 1));
                case OutExpo:
                    return -pow(2, -10 * v) + 1;
                case InOutExpo:
                    if (v < .5) return .5 * pow(2, 20 * v - 10);
                    return 1 - .5 * pow(2, -20 * v + 10);

                case InCirc:
                    return 1 - sqrt(1 - v * v);
                case OutCirc:
                    return sqrt(1 - --v * v);
                case InOutCirc:
                    if ((v *= 2) < 1) return .5 - .5 * sqrt(1 - v * v);
                    return .5 * sqrt(1 - (v -= 2) * v) + .5;

                case InElastic:
                    return -pow(2, -10 + 10 * v) * sin((1 - elastic_const2 - v) * elastic_const);
                case OutElastic:
                    return pow(2, -10 * v) * sin((v - elastic_const2) * elastic_const) + 1;
                case OutElasticHalf:
                    return pow(2, -10 * v) * sin((.5 * v - elastic_const2) * elastic_const) + 1;
                case OutElasticQuarter:
                    return pow(2, -10 * v) * sin((.25 * v - elastic_const2) * elastic_const) + 1;
                case InOutElastic:
                    if ((v *= 2) < 1)
                        return -.5 * pow(2, -10 + 10 * v) * sin((1 - elastic_const2 * 1.5 - v) * elastic_const / 1.5);
                    return .5 * pow(2, -10 * --v) * sin((v - elastic_const2 * 1.5) * elastic_const / 1.5) + 1;

                case InBack:
                    return v * v * ((back_const + 1) * v - back_const);
                case OutBack:
                    return --v * v * ((back_const + 1) * v + back_const) + 1;
                case InOutBack:
                    if ((v *= 2) < 1) return .5 * v * v * ((back_const2 + 1) * v - back_const2);
                    return .5 * ((v -= 2) * v * ((back_const2 + 1) * v + back_const2) + 2);

                case InBounce:
                    v = 1 - v;
                    if (v < bounce_const)
                        return 1 - 7.5625 * v * v;
                    if (v < 2 * bounce_const)
                        return 1 - (7.5625 * (v -= 1.5 * bounce_const) * v + .75);
                    if (v < 2.5 * bounce_const)
                        return 1 - (7.5625 * (v -= 2.25 * bounce_const) * v + .9375);
                    return 1 - (7.5625 * (v -= 2.625 * bounce_const) * v + .984375);
                case OutBounce:
                    if (v < bounce_const)
                        return 7.5625 * v * v;
                    if (v < 2 * bounce_const)
                        return 7.5625 * (v -= 1.5 * bounce_const) * v + .75;
                    if (v < 2.5 * bounce_const)
                        return 7.5625 * (v -= 2.25 * bounce_const) * v + .9375;
                    return 7.5625 * (v -= 2.625 * bounce_const) * v + .984375;
                case InOutBounce:
                    if (v < .5) return .5 - .5 * applyEasing(1 - v * 2,OutBounce);
                    return applyEasing((v - .5) * 2,OutBounce) * .5 + .5;

                case OutPow10:
                    return --v * pow(v, 10) + 1;
                case Jump:
                    //return (v==1)?1:0;
                default:
                    return v;
            }
        }

        static double applyEasing(double v1, double m, double v2, int easing) {
            double p = applyEasing(m, easing);
            return v1 * (1 - p) + v2 * p;
        }

    protected:
        typedef double(*_easing_func)(double);
        static std::vector<_easing_func> easing_funcs;
    };
}



#endif //QT_BB_EASING_H
