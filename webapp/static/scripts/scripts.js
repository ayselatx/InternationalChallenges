// Existing functions for updating progress bars
function updateTemperature(value) {
  const progressBar = document.getElementById("progressBarTemperature");
  let value2 = 20 + value / 2;
  progressBar.style.width = value2 + "%";
  let element = document.getElementById("infoTemperature");  
  element.dataset.valeur = value + "°C";
  element.textContent = element.dataset.valeur; // to show value on progressbar
}

function updateHumidity(value) {
  const progressBar = document.getElementById("progressBarHumidity");
  progressBar.style.width = value + "%";
  let element = document.getElementById("infoHumidity");  
  element.dataset.valeur = value + "%";
  element.textContent = element.dataset.valeur; // to show value on progressbar
}

function updatePressure(value) {
  const progressBar = document.getElementById("progressBarPressure");
  let value2 = value / 20;
  progressBar.style.width = value2 + "%";
  let element = document.getElementById("infoPressure");  
  element.dataset.valeur = value + "hPa";  
  element.textContent = element.dataset.valeur; // to show value on progressbar
}

function startProgress() {
  let progress = 0;
  const interval = setInterval(() => {
      if (progress >= 100) {
          clearInterval(interval); // Stop animation at 100%
      } else {
          progress += 1; // Increase by 1% each iteration
          updateProgress(progress);
      }
  }, 500); // Update every 500ms (0.5s)
}

function updateProgress(value) {
  let progressBar = document.getElementById("progressBarTemperature");
  let overlay = document.getElementById("progressOverlayTemperature");

  let percentage = (value / 50) * 100;  // Assuming max temp is 50°
  progressBar.style.width = "100%";    // Gradient always fills the bar
  overlay.style.width = (100 - percentage) + "%"; // Covers unused area
}

// Initialize Chart.js for plotting temperature, humidity, and pressure
document.addEventListener("DOMContentLoaded", function () {
  // Initialize the chart with empty data
  var timeData = []; // Time (e.g., timestamps, or relative time)
  var tempData = [];
  var humidityData = [];
  var pressureData = [];

  // Function to update the chart data
  function updateChartData() {
      // Add new data to the datasets for each chart
      temperatureChart.data.labels.push(new Date().toLocaleTimeString());  // Add current time for temperature
      temperatureChart.data.datasets[0].data.push(tempData[tempData.length - 1]);

      humidityChart.data.labels.push(new Date().toLocaleTimeString());  // Add current time for humidity
      humidityChart.data.datasets[0].data.push(humidityData[humidityData.length - 1]);

      pressureChart.data.labels.push(new Date().toLocaleTimeString());  // Add current time for pressure
      pressureChart.data.datasets[0].data.push(pressureData[pressureData.length - 1]);

      // Update the charts to display the new data
      temperatureChart.update();
      humidityChart.update();
      pressureChart.update();
  }

 // Temperature chart setup
var temperatureChart = new Chart(document.getElementById('temperatureChart'), {
  type: 'line', // Line chart type for temperature
  data: {
      labels: timeData, // Time on x-axis
      datasets: [
          {
              label: 'Temperature (°C)',
              data: tempData,
              borderColor: 'rgba(255, 99, 132, 1)', // Red for temperature
              backgroundColor: 'rgba(255, 255, 255, 0.2)', // Change background under the line to white (light transparency)
              fill: true
          }
      ]
  },
  options: {
      responsive: true,
      plugins: {
          legend: {
              display: false, // Disable legend to remove checkboxes
          }
      },
      scales: {
          x: {
              type: 'linear',
              position: 'bottom',
              title: {
                  display: true,
                  text: 'Time',
                  color: 'white' // X-axis label color to white
              },
              ticks: {
                  color: 'white' // X-axis ticks color to white
              },
              grid: {
                  color: 'white' // Grid line color to white
              }
          },
          y: {
              beginAtZero: false,
              title: {
                  display: true,
                  text: 'Temperature (°C)',
                  color: 'white' // Y-axis label color to white
              },
              ticks: {
                  color: 'white' // Y-axis ticks color to white
              },
              grid: {
                  color: 'white' // Grid line color to white
              }
          }
      }
  }
});

// Humidity chart setup
var humidityChart = new Chart(document.getElementById('humidityChart'), {
  type: 'line', // Line chart type for humidity
  data: {
      labels: timeData, // Time on x-axis
      datasets: [
          {
              label: 'Humidity (%)',
              data: humidityData,
              borderColor: 'rgba(54, 162, 235, 1)', // Blue for humidity
              backgroundColor: 'rgba(255, 255, 255, 0.2)', // Change background under the line to white (light transparency)
              fill: true
          }
      ]
  },
  options: {
      responsive: true,
      plugins: {
          legend: {
              display: false, // Disable legend to remove checkboxes
          }
      },
      scales: {
          x: {
              type: 'linear',
              position: 'bottom',
              title: {
                  display: true,
                  text: 'Time',
                  color: 'white' // X-axis label color to white
              },
              ticks: {
                  color: 'white' // X-axis ticks color to white
              },
              grid: {
                  color: 'white' // Grid line color to white
              }
          },
          y: {
              beginAtZero: false,
              title: {
                  display: true,
                  text: 'Humidity (%)',
                  color: 'white' // Y-axis label color to white
              },
              ticks: {
                  color: 'white' // Y-axis ticks color to white
              },
              grid: {
                  color: 'white' // Grid line color to white
              }
          }
      }
  }
});

// Pressure chart setup
var pressureChart = new Chart(document.getElementById('pressureChart'), {
  type: 'line', // Line chart type for pressure
  data: {
      labels: timeData, // Time on x-axis
      datasets: [
          {
              label: 'Pressure (hPa)',
              data: pressureData,
              borderColor: 'rgba(75, 192, 192, 1)', // Green for pressure
              backgroundColor: 'rgba(255, 255, 255, 0.2)', // Change background under the line to white (light transparency)
              fill: true
          }
      ]
  },
  options: {
      responsive: true,
      plugins: {
          legend: {
              display: false, // Disable legend to remove checkboxes
          }
      },
      scales: {
          x: {
              type: 'linear',
              position: 'bottom',
              title: {
                  display: true,
                  text: 'Time',
                  color: 'white' // X-axis label color to white
              },
              ticks: {
                  color: 'white' // X-axis ticks color to white
              },
              grid: {
                  color: 'white' // Grid line color to white
              }
          },
          y: {
              beginAtZero: false,
              title: {
                  display: true,
                  text: 'Pressure (hPa)',
                  color: 'white' // Y-axis label color to white
              },
              ticks: {
                  color: 'white' // Y-axis ticks color to white
              },
              grid: {
                  color: 'white' // Grid line color to white
              }
          }
      }
  }
});
});