#include <iostream>
#include <fstream>

typedef std::uint16_t WORD;
typedef std::uint32_t DWORD;
typedef std::int32_t LONG;
typedef unsigned char BYTE;

#pragma pack(push,1)
struct BITMAPFILEHEADER{
  WORD  bfType;      // Тип файла
  DWORD bfSize;      // размер файла
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;   // смещение до поля данных (обычно 54)
};

struct BITMAPINFOHEADER {
	DWORD biSize;           // размер структуры в байтах
	LONG  biWidth;          // ширина в пикселях
	LONG  biHeight;         // высота в пикселях
	WORD  biPlanes;         // всегда должно быть 1
	WORD  biBitCount;       // Кол-во бит на цвет 0 | 1 | 2 | 4 | 8 | 16 | 24 | 32  
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;  // горизонтальное разрешение
	LONG  biYPelsPerMeter;  // вертикальное разрешение
	DWORD biClrUsed;        // кол-во используемых цветов (если используется таблица цветов)
	DWORD biClrImportant;   // кол-во существенных цветов
};
#pragma pack(pop)

struct RGB {
	BYTE Red;
	BYTE Green;
	BYTE Blue;
};

struct RGBA {
	BYTE Red;
	BYTE Green;
	BYTE Blue;
	BYTE Alpha;
};

struct rgbImg {
	RGB** pixels;
	unsigned int width;
	unsigned int height;
};

rgbImg createBMP(unsigned int width, unsigned int height) {
	RGB background = { 0, 0, 0 };
	rgbImg img;
	img.width = width;
	img.height = height;
	img.pixels = new RGB * [height];
	for (unsigned int row = 0; row < height; ++row) {
		img.pixels[row] = new RGB[width];
		for (unsigned int col = 0; col < width; ++col) {
			img.pixels[row][col] = background;
		}
	}
	return img;
}

void freeMemory(rgbImg& img) {
	for (unsigned int row = 0; row < img.height; ++row) {
		delete[] img.pixels[row];
	}
	delete[] img.pixels;
	img.pixels = nullptr;
}

bool saveBMP(const rgbImg & img, const char* filename) {
	std::ofstream outBMP(filename, std::ios_base::binary);
	if (!outBMP)
		return false;

	const int offset = (img.width % 4) ? (4 - (3 * img.width) % 4) : 0;

	// записать BITMAPFILEHEADER
	BITMAPFILEHEADER bmfh;
	char bfType[] = { 'B', 'M' };
	bmfh.bfType = *((WORD*)bfType);
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + img.height * img.width * 3;

	outBMP.write((char*)&bmfh, sizeof(BITMAPFILEHEADER));

	// записать BITMAPINFOHEADER
	BITMAPINFOHEADER bmih;
	bmih.biSize = sizeof(BITMAPINFOHEADER);           // размер структуры в байтах
	bmih.biWidth = img.width;          // ширина в пикселях
	bmih.biHeight = img.height;         // высота в пикселях
	bmih.biPlanes = 1;              // всегда должно быть 1
	bmih.biBitCount = 24;       // Кол-во бит на цвет 0 | 1 | 2 | 4 | 8 | 16 | 24 | 32  
	bmih.biCompression = 0;
	bmih.biSizeImage = bmfh.bfSize - bmfh.bfOffBits;
	bmih.biXPelsPerMeter = 1;  // горизонтальное разрешение
	bmih.biYPelsPerMeter = 1;  // вертикальное разрешение
	bmih.biClrUsed = 0;        // кол-во используемых цветов (если используется таблица цветов)
	bmih.biClrImportant = 0;

	outBMP.write((char*)&bmih, sizeof(BITMAPINFOHEADER));

	// записать img
	BYTE offset_array[4] = { 0 };

	for (unsigned int row = img.height; row > 0; --row) {
		for (unsigned int col = 0; col < img.width; ++col) {
			RGB tmp = img.pixels[row - 1][col];
			std::swap(tmp.Blue, tmp.Red);
			outBMP.write((char*)&(tmp), sizeof(RGB));
		}
		outBMP.write((const char*)offset_array, offset);
	}

	outBMP.close();
	return true;
}

void print(const BITMAPINFOHEADER &x) {
	std::cout << "biSize = " << x.biSize << "\n";
	std::cout << "biWidth = " << x.biWidth << "\n";
	std::cout << "biHeight = " << x.biHeight << "\n";
	std::cout << "biPlanes = " << x.biPlanes << "\n";
	std::cout << "biBitCount = " << x.biBitCount << "\n";
	std::cout << "biCompression = " << x.biCompression << "\n";
	std::cout << "biSizeImage = " << x.biSizeImage << "\n";
	std::cout << "biXPelsPerMeter = " << x.biXPelsPerMeter << "\n";
	std::cout << "biYPelsPerMeter = " << x.biYPelsPerMeter << "\n";
	std::cout << "biClrUsed = " << x.biClrUsed << "\n";
	std::cout << "biClrImportant = " << x.biClrImportant << "\n";
}

bool readBMP(const char* fname, rgbImg& img) {
	std::ifstream inFile(fname, std::ios_base::binary);
	if (!inFile)
		return false;
	BITMAPFILEHEADER bmfh;
	inFile.read((char*)&bmfh, sizeof(bmfh));
	// Проверить тип файла
	if (bmfh.bfType != 256 * int('M') + int('B')) {
		inFile.close();
		return false;
	}

	BITMAPINFOHEADER bmih;
	inFile.read((char*)&bmih, sizeof(bmih));
	print(bmih);

	if (bmih.biCompression != 0) {
		inFile.close();
		return false;
	}

	
	
	freeMemory(img);
	img = createBMP(bmih.biWidth, bmih.biHeight);
	
	if ((bmih.biBitCount == 24)) {
		RGB tmp;
		BYTE offset_array[16] = { 0 };
		const int offset = (img.width % 4) ? (4 - (3 * img.width) % 4) : 0;
		for (unsigned int row = img.height; row > 0; --row) {
			for (unsigned int col = 0; col < img.width; ++col) {
				inFile.read((char*)&tmp, sizeof(RGB));
				std::swap(tmp.Blue, tmp.Red);
				img.pixels[row - 1][col] = tmp;
			}
			inFile.read((char*)offset_array, offset);
		}
	} else if ((bmih.biBitCount == 32)) {
		RGBA tmp;
		BYTE offset_array[16] = { 0 };
		// const int offset = (img.width % 4) ? (4 - (4 * img.width) % 4) : 0;
		for (unsigned int row = img.height; row > 0; --row) {
			for (unsigned int col = 0; col < img.width; ++col) {
				inFile.read((char*)&tmp, sizeof(RGBA));
				img.pixels[row - 1][col].Red = tmp.Blue;
				img.pixels[row - 1][col].Green = tmp.Green;
				img.pixels[row - 1][col].Blue = tmp.Red;
			}
			// inFile.read((char*)offset_array, offset);
		}

	} else if ((bmih.biBitCount == 8)) {
		BYTE tmp;
		BYTE offset_array[16] = { 0 };
		const int offset = (img.width % 4) ? (4 - (1 * img.width) % 4) : 0;
		for (unsigned int row = img.height; row > 0; --row) {
			for (unsigned int col = 0; col < img.width; ++col) {
				inFile.read((char*)&tmp, sizeof(tmp));
				img.pixels[row - 1][col].Red = tmp;
				img.pixels[row - 1][col].Green = tmp;
				img.pixels[row - 1][col].Blue = tmp;
			}
			inFile.read((char*)offset_array, offset);
		}
	}
	else {
		inFile.close();
		return false;
	}
	inFile.close();
	return true;
}

int main(int argc, char * argv[]) {
	RGB brush = {255, 255, 255};
	if (argc != 2) {
		std::cout << "Use: paint filename\n";
		return 0;
	}
	rgbImg img = { nullptr, 0, 0 };
	if (!readBMP(argv[1], img)) {
		std::cout << "Can not read BMP file '" << argv[1] << "'\n";
		return 1;
	}

	if (img.height > 25 && img.width > 25) {
		// Logo
		for (unsigned int row = 0; row < 20; ++row) {
			unsigned int x = img.height + row - 25;
			for (unsigned int col = 0; col < 20; ++col) {
				unsigned int y = img.width + col - 25;
				img.pixels[x][y] = brush;
			}
		}
	}

	saveBMP(img, "out.bmp");
	
	freeMemory(img);
}
