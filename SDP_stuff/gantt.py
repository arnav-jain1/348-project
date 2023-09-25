import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from datetime import datetime

# Given dates
dates = {
    "Requirement Document Completion": (datetime(2023, 9, 10), datetime(2023, 9, 24)),
    "Design Document Completion": (datetime(2023, 9, 21), datetime(2023, 10, 8)),
    "Alpha Version Release": (datetime(2023, 10, 4), datetime(2023, 10, 29)),
    "Beta Version Release": (datetime(2023, 10, 28), datetime(2023, 12, 9)),
    "Final Product Deployment and Documentation Release": (datetime(2023, 12, 2), datetime(2023, 12, 15))
}

# List of blue shades
blue_shades = ['#e0f3ff', '#b3d8ff', '#80bdff', '#4da2ff', '#1a87ff']


fig, ax = plt.subplots(figsize=(10, 7))
y = len(dates)
for idx, (task, (start, end)) in enumerate(dates.items()):
    ax.barh(y, (end - start).days, left=start, align='center', color=blue_shades[idx])
    y -= 1


# Adjusting X-axis ticks to be twice its current frequency using DayLocator
ax.xaxis.set_major_locator(mdates.DayLocator(interval=15))
ax.xaxis.set_major_formatter(mdates.DateFormatter("%m/%d"))

# Shorten the Y-axis labels to "Phase 1", "Phase 2", etc.
phase_labels = ["Phase 1", "Phase 2", "Phase 3", "Phase 4", "Phase 5"]
ax.set_yticks(range(1, 6)) # Set tick locations for Y-axis
ax.set_yticklabels(phase_labels[::-1]) # Set tick labels for Y-axis

# Additional settings
ax.set_xlabel("Dates")
ax.set_title("Gantt Chart")
ax.grid(True, which='both', axis='x', linestyle='--')
plt.tight_layout()
plt.show()
