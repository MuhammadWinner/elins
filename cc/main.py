# =================================================================
#             KODE PYTHON FINAL - VERSI PENGIRIMAN LANGSUNG
# =================================================================
import apm
import matplotlib.pyplot as plt
import os

# --- BAGIAN 1: KONTEN MODEL LANGSUNG DI DALAM SCRIPT ---
# Kita tidak akan menulis ke file lagi. Konten ini akan dikirim langsung ke server.
model_content = """
! crane pendulum model
! https://apmonitor.com/do/index.php/Main/CranePendulum
Model
  ! model parameters
  Parameters
    m1 = 1.0 ! mass of the cart
    m2 = 0.3 ! mass of the pendulum
    l = 0.5  ! length of the pendulum rod
    g = 9.8 ! gravity
  End Parameters

  ! manipulated variable
  Variables
    u = 0, >=-10, <=10 ! force on the cart
  End Variables

  ! state variables
  Variables
    y = 0  ! cart position
    v = 0  ! cart velocity
    theta = 0 ! pendulum angle
    q = 0  ! pendulum angular velocity
  End Variables

  ! intermediates
  Intermediates
    den = m1 + m2 * sin(theta)^2
  End Intermediates

  ! differential equations
  Equations
    ! Perubahan posisi (dy/dt) adalah kecepatan (v)
    $y = v

    ! Percepatan gerobak (cart acceleration)
    $v = (u - m2*sin(theta)*(l*q^2 - g*cos(theta))) / den

    ! Kecepatan sudut pendulum (pendulum angular velocity)
    $q = theta

    ! Percepatan sudut pendulum (pendulum angular acceleration)
    $q = (u*cos(theta) - m2*l*q^2*cos(theta)*sin(theta) + (m1+m2)*g*sin(theta)) / (l*den)
  End Equations
End Model
"""
# --- AKHIR DARI BAGIAN 1 ---


# --- BAGIAN 2: EKSEKUSI UTAMA ---
print("\n--- Memulai Proses Optimasi ---")
s = 'http://byu.apmonitor.com'
a = 'crane_pendulum'

# Membersihkan sesi server
print("🧹 Membersihkan sesi server...")
apm.apm(s,a,'clear all')

# --- PERUBAHAN UTAMA: MENGIRIM KONTEN MODEL BARIS PER BARIS ---
# Ini menggantikan apm_load() untuk menghindari masalah file
print("📤 Mengunggah model langsung dari script...")
# Memecah string model menjadi baris-baris dan mengirim satu per satu
for line in model_content.split('\\n'):
    apm.apm(s, a, line)
# --- AKHIR PERUBAHAN UTAMA ---

print("📤 Mengunggah data 'pendulum.csv'...")
apm.csv_load(s,a,'pendulum.csv') # File data csv masih dibutuhkan

# Mengatur opsi simulasi
print("⚙️  Mengatur opsi simulasi...")
apm.apm_option(s,a,'nlc.imode',6)
apm.apm_info(s,a,'MV','u')
apm.apm_option(s,a,'u.status',1)

# Menyelesaikan model
print("🚀 Menyelesaikan model (Mohon tunggu)...")
output = apm.apm(s,a,'solve')
print("\n--- Pesan dari Server APMonitor ---")
print(output)
print("---------------------------------")


# Mengambil hasil solusi
print("📥 Mengambil hasil...")
try:
    z = apm.apm_sol(s,a)
    print("✅ Solusi berhasil diambil.")
except Exception as e:
    print(f"❌ Error saat mengambil solusi: {e}")
    exit()

# --- BAGIAN 3: PLOTTING HASIL ---
print("📈 Membuat grafik hasil...")

plt.figure(figsize=(10, 8))

# Plot 1: Gaya (u)
plt.subplot(4,1,1)
plt.plot(z['time'], z['u'], 'r-', linewidth=2, label='Gaya (u)')
plt.ylabel('Gaya pada Gerobak')
plt.legend()
plt.grid(True)

# Plot 2: Posisi Gerobak (y)
plt.subplot(4,1,2)
plt.plot(z['time'], z['y'], 'b--', linewidth=2, label='Posisi (y)')
plt.ylabel('Posisi Gerobak')
plt.legend()
plt.grid(True)

# Plot 3: Kecepatan Gerobak (v)
plt.subplot(4,1,3)
plt.plot(z['time'], z['v'], 'g:', linewidth=2, label='Kecepatan (v)')
plt.ylabel('Kecepatan Gerobak')
plt.legend()
plt.grid(True)

# Plot 4: Sudut (theta) dan Kecepatan Sudut (q) Pendulum
plt.subplot(4,1,4)
plt.plot(z['time'], z['theta'], 'm.-', linewidth=2, label='Sudut (theta)')
plt.plot(z['time'], z['q'], 'k.', markersize=2, label='Kecepatan Sudut (q)')
plt.ylabel('Sudut & Kecepatan Sudut')
plt.legend()
plt.grid(True)

plt.xlabel('Waktu (detik)')
plt.tight_layout()
plt.show()

print("\n🎉 Proses selesai!")