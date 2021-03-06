#include <string>
#include <iostream>

/* Workaround. See here:
 * https://github.com/ignf/gilviewer/issues/8 */
#define int_p_NULL (int*)NULL

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>

typedef boost::mpl::vector<
	boost::gil::gray8_image_t,
	boost::gil::gray16_image_t,
	boost::gil::rgb8_image_t,
	boost::gil::rgb16_image_t> img_types;


struct negate {
	typedef void result_type; // required

	template <class View>
	void operator()(const View& source) const {
		typedef typename View::value_type value_type;
		typedef typename boost::gil::channel_type<value_type>::type channel_t;

		const std::size_t channels = boost::gil::num_channels<View>::value;
		const channel_t max_val = (std::numeric_limits<channel_t>::max)();

		for (unsigned int y = 0; y < source.height(); ++y) {
			for (unsigned int x = 0; x < source.width(); ++x) {
				for (unsigned int c = 0; c < channels; ++c) {
					source(x,y)[c] = max_val - source(x,y)[c];
				}
			}
		}
	}
};

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Provide an image path as argument\n";
		return 1;
	}

	std::string file_name(argv[1]);

	boost::gil::any_image<img_types> source;
	boost::gil::png_read_image(file_name, source);

	boost::gil::apply_operation(view(source), negate());

	boost::gil::png_write_view("negate_" + file_name, const_view(source));
}
