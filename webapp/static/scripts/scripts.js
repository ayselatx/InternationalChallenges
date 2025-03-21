// Function to generate a random value within a given range
function getRandomValue(min, max) {
    return Math.floor(Math.random() * (max - min + 1) + min);
}

// Function to update temperature progress bar
function updateTemperature(value) {
    const progressBar = document.getElementById("progressBarTemperature");
    let value2 = 20 + value / 2;
    progressBar.style.width = value2 + "%";
    let element = document.getElementById("infoTemperature");
    element.dataset.valeur = value + "°C";
    element.textContent = element.dataset.valeur;
}

// Function to update humidity progress bar
function updateHumidity(value) {
    const progressBar = document.getElementById("progressBarHumidity"); // Vérifier que l'id est bien le bon
    if (!progressBar) return;
    progressBar.style.width = value + "%";
    let element = document.getElementById("infoHumidity");
    element.dataset.valeur = value + "%";
    element.textContent = element.dataset.valeur;
}

// Function to update pressure progress bar
function updatePressure(value) {
    const progressBar = document.getElementById("progressBarPressure");
    if (!progressBar) return;
    let value2 = value / 20;
    progressBar.style.width = value2 + "%";
    let element = document.getElementById("infoPressure");
    element.dataset.valeur = value + "hPa";
    element.textContent = element.dataset.valeur;
}


// Initialize charts with Chart.js (temperature, humidity, pressure)
document.addEventListener("DOMContentLoaded", function () {
    var temperatureChart = new Chart(document.getElementById('temperatureChart'), {
        type: 'line',
        data: { labels: [], datasets: [{ label: 'Temperature (°C)', data: [], borderColor: 'red', fill: true }] },
        options: { responsive: true, scales: { x: { ticks: { color: 'white' } }, y: { ticks: { color: 'white' } } } }
    });

    var humidityChart = new Chart(document.getElementById('humidityChart'), {
        type: 'line',
        data: { labels: [], datasets: [{ label: 'Humidity (%)', data: [], borderColor: 'blue', fill: true }] },
        options: { responsive: true, scales: { x: { ticks: { color: 'white' } }, y: { ticks: { color: 'white' } } } }
    });

    var pressureChart = new Chart(document.getElementById('pressureChart'), {
        type: 'line',
        data: { labels: [], datasets: [{ label: 'Pressure (hPa)', data: [], borderColor: 'green', fill: true }] },
        options: { responsive: true, scales: { x: { ticks: { color: 'white' } }, y: { ticks: { color: 'white' } } } }
    });

    // Function to generate fake data and update charts
    function updateFakeData() {
        let newTemperature = getRandomValue(0, 50);
        let newHumidity = getRandomValue(20, 100);
        let newPressure = getRandomValue(950, 1050);
        let currentTime = new Date().toLocaleTimeString();

        // Update progress bars
        updateTemperature(newTemperature);
        updateHumidity(newHumidity);
        updatePressure(newPressure);

        // Update chart data
        temperatureChart.data.labels.push(currentTime);
        temperatureChart.data.datasets[0].data.push(newTemperature);
        humidityChart.data.labels.push(currentTime);
        humidityChart.data.datasets[0].data.push(newHumidity);
        pressureChart.data.labels.push(currentTime);
        pressureChart.data.datasets[0].data.push(newPressure);

        // Keep only the last 10 data points
        if (temperatureChart.data.labels.length > 50) {
            temperatureChart.data.labels.shift();
            temperatureChart.data.datasets[0].data.shift();
            humidityChart.data.labels.shift();
            humidityChart.data.datasets[0].data.shift();
            pressureChart.data.labels.shift();
            pressureChart.data.datasets[0].data.shift();
        }

        // Update the charts
        temperatureChart.update();
        humidityChart.update();
        pressureChart.update();
    }

    console.log("setInterval is running...");
    // Automatically update fake data every 2 seconds
    setInterval(updateFakeData, 2000);
});
