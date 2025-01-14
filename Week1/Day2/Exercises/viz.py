from email.mime import base
import matplotlib.pyplot as plt
import pandas as pd

# Read the data files, specifying that there are no headers
df_aos = pd.read_csv('aos.gcc.dat', header=None, delim_whitespace=True)
df_soa = pd.read_csv('soa.gcc.dat', header=None, delim_whitespace=True)

# Assign meaningful column names
df_aos.columns = ['Memory_Footprint', 'Distance', 'DistCheck', 'Total', 'Runtime']
df_soa.columns = ['Memory_Footprint', 'Distance', 'DistCheck', 'Total', 'Runtime']

# Print the data to verify
print(df_aos)
print(df_soa)

# Plot MFLOPS against memory footprint
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.plot(df_aos['Memory_Footprint'], df_aos['Distance'], label='AOS Distance')
plt.plot(df_aos['Memory_Footprint'], df_aos['DistCheck'], label='AOS DistCheck')
plt.plot(df_aos['Memory_Footprint'], df_aos['Total'], label='AOS Total')
plt.plot(df_soa['Memory_Footprint'], df_soa['Distance'], label='SOA Distance')
plt.plot(df_soa['Memory_Footprint'], df_soa['DistCheck'], label='SOA DistCheck')
plt.plot(df_soa['Memory_Footprint'], df_soa['Total'], label='SOA Total')
plt.xlabel('Memory Footprint (kB)')
plt.ylabel('MFLOPS')
plt.title('Performance in MFLOPS vs Memory Footprint')
plt.xscale('log',base=2)
plt.legend()

# Plot runtime against memory footprint
plt.subplot(1, 2, 2)
plt.plot(df_aos['Memory_Footprint'], df_aos['Runtime'], label='AOS Runtime')
plt.plot(df_soa['Memory_Footprint'], df_soa['Runtime'], label='SOA Runtime')
plt.xlabel('Memory Footprint (kB)')
plt.ylabel('Runtime (secs)')
plt.title('Runtime vs Memory Footprint')
plt.xscale('log',base=2)
plt.legend()

plt.tight_layout()
plt.show()
plt.savefig('performance_plots.png')
