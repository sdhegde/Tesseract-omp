#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <sys/time.h>
#include <fstream>
#include <omp.h>
#include <unistd.h>

using namespace std;

extern int n;
extern Boxa* boxes;
extern tesseract::TessBaseAPI *api[];



void f(){
  struct timeval startTime, endTime;
  long elapsedTime;
  
  #pragma omp taskloop private(startTime, endTime, elapsedTime)
  for (int i = 0; i < boxes->n; i++) {      
    BOX* box = boxaGetBox(boxes, i, L_CLONE);
    api[omp_get_thread_num()]->SetRectangle(box->x, box->y, box->w, box->h);
    
    api[omp_get_thread_num()]->Recognize(0);
    
    tesseract::ResultIterator* ri = api[omp_get_thread_num()]->GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_PARA;
    if (ri != 0) {
      do {
        const char* word = ri->GetUTF8Text(level);
        //float conf = ri->Confidence(level);
        //int x1, y1, x2, y2;
        //ri->BoundingBox(level, &x1, &y1, &x2, &y2);
        //printf("word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n", word, conf, x1, y1, x2, y2);
        cout<<omp_get_thread_num()<<" : "<<word<<flush;
        delete[] word;
      } while (ri->Next(level));
    }
  }
}


/*
void f(){
  cout<<"f: "<<n<<endl;
  cout<<"boxes->n: "<<boxes->n<<endl<<flush;
  
  #pragma omp taskloop
  for (int i = 0; i < boxes->n; i++) {
    BOX* box = boxaGetBox(boxes, i, L_CLONE);
    #pragma omp critical
    cout<<omp_get_thread_num()<<" : "<<box->w<<" "<<box->h<<endl<<flush;
    api[omp_get_thread_num()]->SetRectangle(box->x, box->y, box->w, box->h);
    char* ocrResult = api[omp_get_thread_num()]->GetUTF8Text();
    cout<<omp_get_thread_num()<<" : "<<ocrResult<<flush;
    //int conf = api->MeanTextConf();
    //fprintf(stdout, "Box[%d]: x=%d, y=%d, w=%d, h=%d, confidence: %d, text: %s", i, box->x, box->y, box->w, box->h, conf, ocrResult);
    //outText.append("\n");
    //outText.append(ocrResult);
  }
}*/
