# Dekomposisi Masalah

Pada masalah ini, pengguna tidak dapat mengetahui lokasinya,
pengguna mengestimasi posisi dan orientasi menggunakan kamera.
Dengan gambar, pengguna dapat mengetahui posisi dan orientasi
kameranya.

## Masalah

1. Lokasi tidak diketahui, asumsi lokasi memiliki fitur visual yang cukup
2. Perlu mengetahui posisi dan orientasi kamera berdasar gambar

Pada gambar, posisi dan orientasi kamera dapat diketahui menggunakan
beragam metode, misalnya dengan epipolar geometry, triangulasi, dan PnP.
Ketiga metode tersebut dapat menjadi building block untuk membangun
metode yang lebih canggih yaitu visual odometry atau visual SLAM.

## Solusi

Pada implementasi ini, saya mengimplementasikan building block dari
visual odometry sederhana yaitu estimasi camera motion dengan epipolar
geometry dan essential matrix. Dengan solusi ini, masalah dapat didekomposisi menjadi:

### Ekstraksi dan pencocokan fitur, perolehan koordinat 2D fitur pada gambar

Algoritma ekstraksi fitur yang dipilih adalah Oriented FAST karena algoritma ini
dapat memberikan akurasi yang baik dengan performa yang masih dapat dipakai untuk
aplikasi realtime. Setelah fitur terekstraksi, diambil descriptor dari masing-masing
fitur dengan menggunakan BRIEF. Descriptor tersebut digunakan untuk pencocokan fitur
menggunakan Hamming-BruteForce. Setelah didapat fitur yang cocok, diambil fitur inlier
yang memiliki hamming distance kecil.

Implementasi dapat dilihat di [Feature](../src/feature_method.cpp).
Pada implementasi tersebut saya menggunakan method yang tersedia di OpenCV.

### Gerak kamera, perolehan koordinat 3D gerak kamera berdasarkan gambar

$$
\mathbf{p}_2^T \mathbf{K}^{-T} \mathbf{t}^{\wedge} \mathbf{R} \mathbf{K}^{-1} \mathbf{p}_1 = 0
$$

Dengan menggunakan fitur yang telah diekstraksi dan dicocokkan, gerak kamera dapat
ditentukan dengan memanfaatkan epipolar geometry. Epipolar constraint dapat
memberikan translasi dan rotasi kamera dengan fundamental matrix $\mathbf{F}$ dan essential
matrix $\mathbf{E}$.

$$
\begin{aligned}
\mathbf{E} &= \mathbf{t}^{\wedge} \mathbf{R} \\
\mathbf{F} &= \mathbf{K}^{-T} \mathbf{E} \mathbf{K}^{-1} \\
\mathbf{x}_2^T \mathbf{E} \mathbf{x}_1 &= \mathbf{p}_2^T \mathbf{F} \mathbf{p}_1 = 0
\end{aligned}
$$

Dengan menggunakan dekomposisi $\mathbf{E}$, diperoleh matriks rotasi $\mathbf{R}$ dan vektor translasi $\mathbf{t}$.

Implementasi dapat dilihat di [Camera Motion](../src/camera_motion.cpp).
Pada implementasi tersebut saya menggunakan method yang tersedia di OpenCV.

Kelemahan dari metode ini adalah up to a scale, yang mana besaran pada matriks yang dihasilkan
tidak memiliki skala. Hal ini merupakan keterbatasan informasi yaitu hanya terdapat gambar
dengan perspektif berbeda dari satu kamera. Ini dapat diatasi dengan menggunakan informasi lain seperti
akselerasi dan orientasi dari IMU atau menggunakan kamera stereo sehingga depth dengan metric scale dapat diambil.

### Hasil, galat, dan keterbatasan solusi

Dengan menggunakan gambar sample ![gambar1](../sample/img1.jpg) dan ![gambar2](../sample/img2.jpg) didapat hasil
Dari gambar di atas dihasilkan ekstraksi dan pencocokan fitur ![feature match](../sample/feature_matching_res.jpg)
Fitur fitur cocok yang didapatkan dari gambar tersebut dan intrinsic kamera yang diketahui digunakan untuk menghitung essential matrix. Dengan
dekomposisi essential matrix didapat matrix rotasi dan translasi kamera.

posisi dan orientasi kamera dalam homogeneous matrix:

```
Camera pose:
  0.999237 -0.0370057  -0.012498   0.393598
 0.0371642   0.999228  0.0126983   0.365572
 0.0120184 -0.0131531   0.999841  -0.843467
         0          0          0          1
```

Translasi yang dihasilkan dinormalisasi sehingga normnya berukuran 1.
Hal ini merupakan keterbatasan solusi dan informasi karena menggunakan
kamera monokular dan tidak ada informasi lain selain fitur seperti
informasi dari IMU.
