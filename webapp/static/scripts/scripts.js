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
    const progressBar = document.getElementById("progressBarHumidity");
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

