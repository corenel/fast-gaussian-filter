#pragma once
#include <math.h>
#include "base.hpp"

static int* boxes_for_gauss(double sigma, int n) {
  double w_ideal = sqrt((12 * sigma * sigma / n) + 1);
  int wl = (int)floor(w_ideal);
  if (wl % 2 == 0) wl--;

  int wu = wl + 2;

  double m_ideal =
      (12 * sigma * sigma - n * wl * wl - 4 * n * wl - 3 * n) / (-4 * wl - 4);
  int m = round(m_ideal);

  auto sizes = new int[n];
  for (int i = 0; i < n; i++) {
    sizes[i] = i < m ? wl : wu;
  }
  return sizes;
}

static unsigned char* get_pixel(unsigned char* source, int index) {
  return source + index * 3;
}

static void set_pixel(unsigned char* source, int index, int r, int g, int b) {
  if (r < 0) r = 0;
  if (r > 255) r = 255;

  if (g < 0) g = 0;
  if (g > 255) g = 255;

  if (b < 0) b = 0;
  if (b > 255) b = 255;

  *(source + index * 3) = r;
  *(source + index * 3 + 1) = g;
  *(source + index * 3 + 2) = b;
}

static void box_blur_h(unsigned char* source, unsigned char* target, int w,
                       int h, int radius) {
  double iarr = (double)1 / (radius + radius + 1);
  for (int i = 0; i < h; i++) {
    int ti = i * w;
    int li = ti;
    int ri = ti + radius;
    unsigned char* fv = get_pixel(source, ti);
    unsigned char* lv = get_pixel(source, ti + w - 1);

    unsigned current_r = *fv * (radius + 1);
    unsigned current_g = *(fv + 1) * (radius + 1);
    unsigned current_b = *(fv + 2) * (radius + 1);

    for (int j = 0; j < radius; j++) {
      unsigned char* pixel = get_pixel(source, ti + j);
      current_r += *pixel;
      current_g += *(pixel + 1);
      current_b += *(pixel + 2);
    }

    for (int j = 0; j <= radius; j++) {
      unsigned char* pixel = get_pixel(source, ri++);
      current_r += (*pixel - *fv);
      current_g += (*(pixel + 1) - *(fv + 1));
      current_b += (*(pixel + 2) - *(fv + 2));

      set_pixel(target, ti++, current_r * iarr, current_g * iarr,
                current_b * iarr);
    }

    for (int j = radius + 1; j < w - radius; j++) {
      unsigned char* first_pixel = get_pixel(source, ri++);
      unsigned char* second_pixel = get_pixel(source, li++);

      current_r += (*first_pixel - *second_pixel);
      current_g += (*(first_pixel + 1) - *(second_pixel + 1));
      current_b += (*(first_pixel + 2) - *(second_pixel + 2));

      set_pixel(target, ti++, current_r * iarr, current_g * iarr,
                current_b * iarr);
    }

    for (int j = w - radius; j < w; j++) {
      unsigned char* pixel = get_pixel(source, li++);

      current_r += (*lv - *pixel);
      current_g += (*(lv + 1) - *(pixel + 1));
      current_b += (*(lv + 2) - *(pixel + 2));

      set_pixel(target, ti++, current_r * iarr, current_g * iarr,
                current_b * iarr);
    }
  }
}

static void box_blur_t(unsigned char* source, unsigned char* target, int w,
                       int h, int radius) {
  double iarr = (double)1 / (radius + radius + 1);
  for (int i = 0; i < w; i++) {
    int ti = i;
    int li = ti;
    int ri = ti + radius * w;

    unsigned char* fv = get_pixel(source, ti);
    unsigned char* lv = get_pixel(source, ti + w * (h - 1));

    unsigned current_r = *fv * (radius + 1);
    unsigned current_g = *(fv + 1) * (radius + 1);
    unsigned current_b = *(fv + 2) * (radius + 1);

    for (int j = 0; j < radius; j++) {
      unsigned char* pixel = get_pixel(source, ti + j * w);
      current_r += *pixel;
      current_g += *(pixel + 1);
      current_b += *(pixel + 2);
    }

    for (int j = 0; j <= radius; j++) {
      unsigned char* pixel = get_pixel(source, ri);
      current_r += (*pixel - *fv);
      current_g += (*(pixel + 1) - *(fv + 1));
      current_b += (*(pixel + 2) - *(fv + 2));

      set_pixel(target, ti, current_r * iarr, current_g * iarr,
                current_b * iarr);

      ri += w;
      ti += w;
    }

    for (int j = radius + 1; j < h - radius; j++) {
      unsigned char* first_pixel = get_pixel(source, ri);
      unsigned char* second_pixel = get_pixel(source, li);

      current_r += (*first_pixel - *second_pixel);
      current_g += (*(first_pixel + 1) - *(second_pixel + 1));
      current_b += (*(first_pixel + 2) - *(second_pixel + 2));

      set_pixel(target, ti, current_r * iarr, current_g * iarr,
                current_b * iarr);

      li += w;
      ri += w;
      ti += w;
    }

    for (int j = h - radius; j < h; j++) {
      unsigned char* pixel = get_pixel(source, li);

      current_r += (*lv + *pixel);
      current_g += (*(lv + 1) + *(pixel + 1));
      current_b += (*(lv + 2) + *(pixel + 2));

      set_pixel(target, ti, current_r * iarr, current_g * iarr,
                current_b * iarr);

      li += w;
      ti += w;
    }
  }
}

static void box_blur(unsigned char* source, unsigned char* target, int w, int h,
                     int radius) {
  memcpy(target, source, sizeof(unsigned char) * w * h * 3);
  box_blur_h(target, source, w, h, radius);
  box_blur_t(source, target, w, h, radius);
}

class FastestBlur : public BaseFilter {
 public:
  FastestBlur(const int& width, const int& height, const int& channels,
              const int& kernel_size = 3);
  void* execute(void* input) override;
};
