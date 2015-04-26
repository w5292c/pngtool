#include <QFile>
#include <pnglite.h>
#include <QDebug>
#include <QImage>
#include <QtCore/qcoreapplication.h>

int main(int argc, char **argv)
{
  QCoreApplication app(argc, argv);

  if (argc < 2) {
    qWarning() << "no image filename";
    return 1;
  }
  const QString filename = QString::fromLatin1(argv[1]);
  qDebug() << "Trying to open:" << filename;

  QImage image(filename);
  qDebug() << "Opened:" << image.format() << "," <<image.byteCount();
  const QImage &out = image.convertToFormat(QImage::Format_RGB16);
  qDebug() << "Opened:" << out.format() << "," << out.byteCount();
  const uchar *dataPtr = out.constBits();
  const QByteArray data((const char *)dataPtr, out.byteCount());
  QDataStream dataStream(data);
  dataStream.setByteOrder(QDataStream::LittleEndian);
  quint16 word;
  QFile file("out.bin");
  file.open(QIODevice::WriteOnly);
  QDataStream outFile(&file);
  outFile.setByteOrder(QDataStream::BigEndian);
  for (int i = 0; i < out.byteCount()/2; ++i) {
    dataStream >> word;
    outFile << word;
  }

#if 0
  png_t png;
  const int res = png_open_file(&png, argv[1]);
  qDebug() << "Opened:" << res;
  png_print_info(&png);

  png_close_file(&png);
#endif
  return 0;
}
