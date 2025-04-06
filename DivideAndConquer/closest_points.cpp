#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

class Point
{
public:
    double x, y;

    Point(double x, double y) : x(x), y(y) {}

    static double distance(const Point &p1, const Point &p2)
    {
        return std::sqrt(std::pow(p2.y - p1.y, 2) + std::pow(p2.x - p1.x, 2));
    }
};

std::tuple<Point *, Point *, double> closest_brute_force(const std::vector<Point *> &points)
{
    double min_dist = std::numeric_limits<double>::infinity();
    Point *p1 = nullptr;
    Point *p2 = nullptr;

    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            double d = Point::distance(*points[i], *points[j]);
            if (d < min_dist)
            {
                min_dist = d;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }

    return std::make_tuple(p1, p2, min_dist);
}

std::tuple<Point *, Point *, double> rec(const std::vector<Point *> &xsorted, const std::vector<Point *> &ysorted)
{
    size_t n = xsorted.size();

    if (n <= 3)
    {
        return closest_brute_force(xsorted);
    }
    else
    {
        Point *midpoint = xsorted[n / 2];
        std::vector<Point *> xsorted_left(xsorted.begin(), xsorted.begin() + n / 2);
        std::vector<Point *> xsorted_right(xsorted.begin() + n / 2, xsorted.end());

        std::vector<Point *> ysorted_left, ysorted_right;
        std::copy_if(ysorted.begin(), ysorted.end(), std::back_inserter(ysorted_left),
                     [midpoint](const Point *p)
                     { return p->x <= midpoint->x; });
        std::copy_if(ysorted.begin(), ysorted.end(), std::back_inserter(ysorted_right),
                     [midpoint](const Point *p)
                     { return p->x > midpoint->x; });

        auto [p1_left, p2_left, delta_left] = rec(xsorted_left, ysorted_left);
        auto [p1_right, p2_right, delta_right] = rec(xsorted_right, ysorted_right);

        auto [p1, p2, delta] = (delta_left < delta_right) ? std::make_tuple(p1_left, p2_left, delta_left)
                                                          : std::make_tuple(p1_right, p2_right, delta_right);

        std::vector<Point *> in_band;
        std::copy_if(ysorted.begin(), ysorted.end(), std::back_inserter(in_band),
                     [midpoint, delta](const Point *p)
                     {
                         return midpoint->x - delta < p->x && p->x < midpoint->x + delta;
                     });

        for (size_t i = 0; i < in_band.size(); ++i)
        {
            for (size_t j = i + 1; j < std::min(i + 7, in_band.size()); ++j)
            {
                double d = Point::distance(*in_band[i], *in_band[j]);
                if (d < delta)
                {
                    p1 = in_band[i];
                    p2 = in_band[j];
                    delta = d;
                }
            }
        }

        return std::make_tuple(p1, p2, delta);
    }
}

std::tuple<Point *, Point *, double> closest(const std::vector<Point *> &points)
{
    std::vector<Point *> xsorted = points;
    std::vector<Point *> ysorted = points;

    std::sort(xsorted.begin(), xsorted.end(), [](const Point *a, const Point *b)
              { return a->x < b->x; });
    std::sort(ysorted.begin(), ysorted.end(), [](const Point *a, const Point *b)
              { return a->y < b->y; });

    return rec(xsorted, ysorted);
}

int main()
{
    // Example usage
    std::vector<Point *> points;
    points.push_back(new Point(0, 0));
    points.push_back(new Point(1, 1));
    points.push_back(new Point(3, 3));
    points.push_back(new Point(3, 2));
    points.push_back(new Point(4, 5));

    auto [p1, p2, min_dist] = closest(points);

    std::cout << "Closest pair points: (" << p1->x << ", " << p1->y << ") and (" << p2->x << ", " << p2->y << ")" << std::endl;
    std::cout << "Closest pair distance: " << min_dist << std::endl;

    // Free memory
    for (Point *p : points)
    {
        delete p;
    }

    return 0;
}