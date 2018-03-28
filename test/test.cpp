template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
  for (; first != last; ++first) {
    f(*first);
  }
  return f;
}


std::vector<double> v{ 1.0, 2.2, 4.0, 5.5, 7.2 };
double r = 4.0;
std::for_each(v.begin(), v.end(), [&](double & v) { v += r; });
std::for_each(v.begin(), v.end(), [](double v) { std::cout << v << " "; });
