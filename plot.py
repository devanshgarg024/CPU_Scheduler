import pandas as pd
import sys

# Check for a command-line argument to determine if we should show the plot.
show_plot = '--show' in sys.argv

if not show_plot:
    import matplotlib
    matplotlib.use('Agg')  # Use a non-interactive backend to prevent pop-up
import matplotlib.pyplot as plt

# --- Create a sample CSV for demonstration if it doesn't exist ---
try:
    df = pd.read_csv('process_schedule.csv')
except FileNotFoundError:
    print("process_schedule.csv not found. Creating a sample file.")
    data = {
        'pid': [1, 2, 3, 1, 4, 2, 3],
        'start_time': [0, 5, 8, 12, 15, 19, 22],
        'end_time': [5, 8, 12, 15, 19, 22, 25]
    }
    df = pd.DataFrame(data)
    df.to_csv('process_schedule.csv', index=False)
# ----------------------------------------------------------------

# Set dark theme style
plt.style.use('dark_background')

# Read the CSV file
df = pd.read_csv('process_schedule.csv')

# Create a figure with a dark background
fig, ax = plt.subplots(figsize=(14, 7), facecolor='#1c1c1c')

# High-contrast color palette
high_contrast_colors = [
    '#ff0000', '#00ff00', '#ffff00', '#00ffff',
    '#ff00ff', '#ffa500', '#7fff00', '#ff69b4',
    '#00bfff', '#ffd700'
]

# --- MODIFICATION START ---
# Define a y-position for the consolidated CPU timeline bar
consolidated_y_pos = 0
# --- MODIFICATION END ---

# --- MODIFICATION START ---
# Create a mapping from PID to an evenly spaced y-position
unique_pids = sorted(df['pid'].unique())
pid_to_y_map = {pid: i + 1 for i, pid in enumerate(unique_pids)}
# --- MODIFICATION END ---

# Plot each process as a horizontal bar
for _, row in df.iterrows():
    process_color = high_contrast_colors[row['pid'] % len(high_contrast_colors)]

    # Plot the individual timeline for each process ID
    ax.hlines(y=pid_to_y_map[row['pid']],
              xmin=row['start_time'],
              xmax=row['end_time'],
              linewidth=10,
              color=process_color)

    # --- MODIFICATION START ---
    # Plot the segment on the single, consolidated CPU timeline bar
    ax.hlines(y=consolidated_y_pos,
              xmin=row['start_time'],
              xmax=row['end_time'],
              linewidth=20,  # Make this bar thicker to stand out
              color=process_color)
    # --- MODIFICATION END ---


# Customize the plot
ax.set_title('Process Schedule Timeline', color='white', fontsize=16, pad=20)
ax.set_xlabel('Time (units)', color='white', fontsize=12)
ax.set_ylabel('Process', color='white', fontsize=12)

# Set grid style
ax.grid(True, axis='x', linestyle='--', alpha=0.4, color='#a0a0a0')

# --- MODIFICATION START ---
# Adjust y-axis to include the new consolidated bar
y_ticks = [consolidated_y_pos] + list(pid_to_y_map.values())
y_labels = ['CPU Timeline'] + [f'Process {pid}' for pid in unique_pids]

ax.set_yticks(y_ticks)
ax.set_yticklabels(y_labels)
# --- MODIFICATION END ---

ax.tick_params(axis='both', colors='white')

# Create legend with a dark background
# The legend handles are created manually to avoid duplicates
legend_handles = [plt.Line2D([0], [0], color=high_contrast_colors[pid % len(high_contrast_colors)], lw=4) for pid in unique_pids]
legend_labels = [f'Process {pid}' for pid in unique_pids]

legend = ax.legend(legend_handles,
                   legend_labels,
                   bbox_to_anchor=(1.05, 1),
                   loc='upper left',
                   facecolor='#2c2c2c',
                   edgecolor='white',
                   labelcolor='white',
                   title='Processes')

plt.setp(legend.get_title(), color='white')

# Adjust layout and save
plt.tight_layout(rect=[0, 0, 0.85, 1]) # Adjust rect to make space for legend
plt.savefig('process_schedule_dark.png',
            facecolor=fig.get_facecolor(),
            dpi=300,
            bbox_inches='tight')

if show_plot:
    plt.show()