//#include "ImageWrapper.h"
//#include "MosaicFragment.h"
//#include "ImageIndexBuilder.h"


//ImageIndexBuilder::ImageIndexBuilder(const std::vector<std::string>& resources)
//{
//	std::ofstream ofile("index.txt");

//	std::vector<std::string>::const_iterator it, endIt = resources.end();
//	for(it = resources.begin(); it != endIt; ++it)
//	{
//		try
//		{
//			ImageWrapperPtr image(new ImageWrapper(*it));
//			//if(image->width() >= 600 && image->height() >= 600)
//			{
//				printf("Indexing file %s\n", (*it).c_str());
//				MosaicFragment fragment(image);
//				fragment.calculateAveragColor();
//				Color avColor = fragment.averageColor();

//				ofile << *it << " " << (int)avColor.r << " " << (int)avColor.g << " " << (int)avColor.b << std::endl;
//				ofile.flush();
//			}

//		}
//		catch(std::exception& e)
//		{
//			std::cout << e.what() << std::endl;
//		}
//	}
//}


//ImageIndexBuilder::~ImageIndexBuilder()
//{
//}
