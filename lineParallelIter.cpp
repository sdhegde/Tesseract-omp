#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <sys/time.h>
#include <fstream>
#include <omp.h>

using namespace std;

int n;
Boxa* boxes;
tesseract::TessBaseAPI *api[4];
extern void f();

int main(int argc, char* argv[])
{
  struct timeval startTime, endTime;
  long elapsedTime;
  
  #pragma omp parallel
  {
    api[omp_get_thread_num()] = new tesseract::TessBaseAPI();
    api[omp_get_thread_num()]->Init(NULL, "eng");
    
    Pix *image = pixRead(argv[1]);
    api[omp_get_thread_num()]->SetImage(image);
    
    n=99;

    #pragma omp single
    { 
      api[omp_get_thread_num()]->SetPageSegMode(tesseract::PSM_AUTO);
      boxes = api[omp_get_thread_num()]->GetComponentImages(tesseract::RIL_PARA, true, NULL, NULL);
      printf("Found %d textline image components.\n", boxes->n);
    }
    
    #pragma omp single
    {
      #pragma omp task
      f();      
    }
    
    
    api[omp_get_thread_num()]->End();
    pixDestroy(&image);
  }

	return 0;
}
