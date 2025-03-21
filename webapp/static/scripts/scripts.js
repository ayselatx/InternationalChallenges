<<<<<<< Updated upstream
// Function to update temperature progress bar
=======
// Function to generate a random value within a given range
function getRandomValue(min, max) {
    return Math.floor(Math.random() * (max - min + 1) + min);
}

// Function to update temperature progress bar (0°C to 50°C)
>>>>>>> Stashed changes
function updateTemperature(value) {
    const overlay = document.getElementById("progressOverlayTemperature");
    if (!overlay) return;

    let percentage = ((value - 0) / (50 - 0)) * 100; // Normalize to 0-100%
    percentage = Math.max(0, Math.min(100, percentage)); // Ensure within bounds

    overlay.style.width = (100 - percentage) + "%"; // Adjust white overlay

    let element = document.getElementById("infoTemperature");
    element.dataset.valeur = value + "°C";
    element.textContent = element.dataset.valeur;
}

// Function to update humidity progress bar (0% to 100%)
function updateHumidity(value) {
<<<<<<< Updated upstream
    const progressBar = document.getElementById("progressBarHumidity");
    if (!progressBar) return;
    progressBar.style.width = value + "%";
=======
    const overlay = document.getElementById("progressOverlayHumidity");
    if (!overlay) return;

    let percentage = Math.max(0, Math.min(100, value)); // Ensure within bounds

    overlay.style.width = (100 - percentage) + "%"; // Adjust white overlay

>>>>>>> Stashed changes
    let element = document.getElementById("infoHumidity");
    element.dataset.valeur = value + "%";
    element.textContent = element.dataset.valeur;
}

// Function to update pressure progress bar (900hPa to 1100hPa)
function updatePressure(value) {
    const overlay = document.getElementById("progressOverlayPressure");
    if (!overlay) return;

    let percentage = ((value - 900) / (1100 - 900)) * 100; // Normalize between 900-1100hPa
    percentage = Math.max(0, Math.min(100, percentage)); // Ensure within bounds

    overlay.style.width = (100 - percentage) + "%"; // Adjust white overlay

    let element = document.getElementById("infoPressure");
    element.dataset.valeur = value + "hPa";
    element.textContent = element.dataset.valeur;
}

<<<<<<< Updated upstream
=======


// Initialize charts with Chart.js (temperature, humidity, pressure)
>>>>>>> Stashed changes
document.addEventListener("DOMContentLoaded", function () {
    // Référence aux éléments HTML pour les graphiques
    const temperatureCanvas = document.getElementById('temperatureChart');
    const humidityCanvas = document.getElementById('humidityChart');
    const pressureCanvas = document.getElementById('pressureChart');

    // Initialisation des graphiques avec Chart.js
    var temperatureChart = new Chart(temperatureCanvas, {
        type: 'line',
        data: {
            labels: [],  // Étiquettes des données (ici, c'est le timestamp)
            datasets: [{
                label: 'Temperature (°C)',
                data: [],  // Données de température
                borderColor: 'red',  // Couleur de la ligne
                fill: true  // Remplir la zone sous la courbe
            }]
        },
        options: {
            responsive: true,
            scales: {
                x: {
                    ticks: { color: 'white' }
                },
                y: {
                    ticks: { color: 'white' }
                }
            }
        }
    });

    var humidityChart = new Chart(humidityCanvas, {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'Humidity (%)',
                data: [],
                borderColor: 'blue',
                fill: true
            }]
        },
        options: {
            responsive: true,
            scales: {
                x: { ticks: { color: 'white' } },
                y: { ticks: { color: 'white' } }
            }
        }
    });

    var pressureChart = new Chart(pressureCanvas, {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'Pressure (hPa)',
                data: [],
                borderColor: 'green',
                fill: true
            }]
        },
        options: {
            responsive: true,
            scales: {
                x: { ticks: { color: 'white' } },
                y: { ticks: { color: 'white' } }
            }
        }
    });

    // Fonction pour récupérer les données du serveur Django et mettre à jour les graphiques
    function fetchSensorData() {
        fetch('/getSensorData/')
            .then(response => response.json())
            .then(data => {
                console.log(data);  // Vérifier les données récupérées

                data.forEach(entry => {
                    const currentTime = entry.timestamp;  // Utiliser le timestamp pour l'axe x

                    // Mettre à jour les barres de progression
                    updateTemperature(entry.temperature);
                    updateHumidity(entry.humidity);
                    updatePressure(entry.pressure);

                    // Mettre à jour les données des graphiques
                    temperatureChart.data.labels.push(currentTime);
                    temperatureChart.data.datasets[0].data.push(entry.temperature);
                    humidityChart.data.labels.push(currentTime);
                    humidityChart.data.datasets[0].data.push(entry.humidity);
                    pressureChart.data.labels.push(currentTime);
                    pressureChart.data.datasets[0].data.push(entry.pressure);

                    // Garder uniquement les 10 dernières données
                    if (temperatureChart.data.labels.length > 10) {
                        temperatureChart.data.labels.shift();
                        temperatureChart.data.datasets[0].data.shift();
                        humidityChart.data.labels.shift();
                        humidityChart.data.datasets[0].data.shift();
                        pressureChart.data.labels.shift();
                        pressureChart.data.datasets[0].data.shift();
                    }
                });

                // Mettre à jour les graphiques
                temperatureChart.update();
                humidityChart.update();
                pressureChart.update();
            })
            .catch(error => console.error('Error fetching sensor data:', error));
    }

    // Appeler la fonction pour récupérer les données toutes les 2 secondes
    setInterval(fetchSensorData, 2000);
});

