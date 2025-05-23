import pandas as pd
import matplotlib.pyplot as plt

# CSV 불러오기
df = pd.read_csv("matrix_vs_cost.csv")

# 그래프 그리기
plt.figure(figsize=(10, 6))
plt.plot(df['matrix_count'], df['min_cost'], marker='o', linewidth=2)

plt.title("Matrix Count vs. Minimum Multiplication Cost")
plt.xlabel("Matrix Count")
plt.ylabel("Minimum Cost / Matrix Count")
plt.grid(True)
plt.tight_layout()
plt.show()
