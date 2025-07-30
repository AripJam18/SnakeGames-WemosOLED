# SnakeGames-WemosOLED
🐍 Snake Game di Wemos D1 Mini + OLED
🎮 Deskripsi Proyek
Proyek ini adalah implementasi game Snake klasik menggunakan board Wemos D1 Mini (ESP8266) dengan layar OLED 0.96" (SSD1306, I2C), dilengkapi 4 tombol arah dan buzzer aktif untuk efek suara.

Game menampilkan:

Score & Timer

Area bermain

Snake yang bertumbuh

Makanan random

Buzzer saat makan dan game over

🛠️ Perangkat Keras
Komponen	Jumlah	Catatan
Wemos D1 Mini	1	ESP8266 board
OLED 0.96" I2C	1	Alamat I2C: 0x3C
Push Button	4	Untuk arah: atas, bawah, kiri, kanan
Resistor 10K	4	Pull-down untuk tombol (opsional, gunakan INPUT_PULLUP)
Buzzer Aktif	1	Untuk efek suara
Breadboard + Kabel Jumper	1 set	Untuk perakitan

🧩 Wiring
Fungsi	Pin ESP8266 (Wemos D1 Mini)
OLED SDA	D2
OLED SCL	D1
UP	D5
DOWN	D6
LEFT	D7
RIGHT	D3
BUZZER	D4

Tombol dihubungkan ke GND dan pin D5–D3 (gunakan INPUT_PULLUP).

📦 Library yang Digunakan
Adafruit GFX

Adafruit SSD1306

🧠 Struktur Game
1. Variabel Utama
snakeX[], snakeY[] — array posisi seluruh bagian ular

length — panjang ular

dirX, dirY — arah gerak (incremental)

foodX, foodY — posisi makanan

score — skor saat ini

startTime — waktu mulai

2. setup()
Inisialisasi OLED, tombol, buzzer

Set posisi awal ular

Spawn makanan pertama

3. loop()
Baca input tombol dan arahkan ular

Gerakkan ular

Cek tabrakan dengan dinding dan diri sendiri

Cek jika makan makanan

Gambar ulang layar (OLED)

Delay kecil (kecepatan)

4. handleInput()
Deteksi tombol ditekan dan ubah arah gerak

5. spawnFood()
Tempatkan makanan di posisi acak dalam grid

6. drawScreen()
Menampilkan:

Skor dan waktu

Area permainan

Snake (dengan fillRect)

Makanan

7. beep()
Fungsi untuk membunyikan buzzer aktif

8. gameOver()
Buzzer 3 kali

Tampilkan “Game Over” dan berhenti program

📺 Tampilan Layar (OLED)
Baris atas: Score dan Time

Kotak di bawah: Area bermain 120×40 px

Snake: kotak 4×4 px

Makanan: kotak 4×4 px

🎵 Efek Suara (Buzzer)
Saat makan makanan → beep(50)

Saat game over → 3x beep(100)

Buzzer aktif hanya perlu HIGH/LOW untuk menyala. Jika kamu menggunakan buzzer pasif, gunakan tone().

🚫 Game Over
Game berakhir jika:

Ular menabrak dinding

Ular menabrak tubuhnya sendiri

Setelah game over, perangkat masuk ke loop tak terbatas (while(1);) untuk berhenti.

📌 Perluasan (Opsional)
Fitur lanjutan yang bisa ditambahkan:

Simpan high score di EEPROM

Level dengan kecepatan meningkat

Obstacle (rintangan)

Tampilan animasi game over

Menu pemilihan game lain
