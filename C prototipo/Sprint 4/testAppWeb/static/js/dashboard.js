document.addEventListener('DOMContentLoaded', () => {
    const tableBody = document.querySelector('#data-table tbody');

    // Fetch de datos desde la API
    fetch('/api/datos')
        .then(response => {
            if (!response.ok) {
                throw new Error('Error en la respuesta de la API');
            }
            return response.json();
        })
        .then(data => {
            // Mostrar datos en la consola para depuración
            console.log(data);

            // Actualizar la tabla con los últimos 10 registros
            tableBody.innerHTML = data.map(d => `
                <tr>
                    <td>${d.nodo_id}</td>
                    <td>${d.temperatura.toFixed(2)}</td>
                    <td>${d.humedad.toFixed(2)}</td>
                    <td>${d.luz_ambiente}</td>
                    <td>${d.humedad_suelo_cap}</td>
                    <td>${d.humedad_suelo_res}</td>
                    <td>${d.nivel_agua}</td>
                    <td>${d.dispositivo_id}</td>
                </tr>`).join('');

            // Preparar datos para los gráficos
            const labels = data.map(d => `Nodo ${d.nodo_id}`);
            const tempData = data.map(d => d.temperatura);
            const humData = data.map(d => d.humedad);
            const luzData = data.map(d => d.luz_ambiente);

            // Crear gráficos con Chart.js
            const tempCtx = document.getElementById('tempChart').getContext('2d');
            const humCtx = document.getElementById('humChart').getContext('2d');
            const luzCtx = document.getElementById('luzChart').getContext('2d');

            // Gráfico de Temperatura
            new Chart(tempCtx, {
                type: 'line',
                data: {
                    labels: labels,
                    datasets: [{
                        label: 'Temperatura (°C)',
                        data: tempData,
                        backgroundColor: 'rgba(255, 99, 132, 0.2)',
                        borderColor: 'rgba(255, 99, 132, 1)',
                        borderWidth: 1,
                        fill: true,
                    }]
                },
                options: {
                    responsive: true,
                    scales: {
                        y: {
                            beginAtZero: true
                        }
                    }
                }
            });

            // Gráfico de Humedad
            new Chart(humCtx, {
                type: 'line',
                data: {
                    labels: labels,
                    datasets: [{
                        label: 'Humedad (%)',
                        data: humData,
                        backgroundColor: 'rgba(54, 162, 235, 0.2)',
                        borderColor: 'rgba(54, 162, 235, 1)',
                        borderWidth: 1,
                        fill: true,
                    }]
                },
                options: {
                    responsive: true,
                    scales: {
                        y: {
                            beginAtZero: true
                        }
                    }
                }
            });

            // Gráfico de Luz Ambiente
            new Chart(luzCtx, {
                type: 'line',
                data: {
                    labels: labels,
                    datasets: [{
                        label: 'Luz Ambiente',
                        data: luzData,
                        backgroundColor: 'rgba(255, 206, 86, 0.2)',
                        borderColor: 'rgba(255, 206, 86, 1)',
                        borderWidth: 1,
                        fill: true,
                    }]
                },
                options: {
                    responsive: true,
                    scales: {
                        y: {
                            beginAtZero: true
                        }
                    }
                }
            });
        })
        .catch(error => {
            console.error('Error al cargar datos:', error);
            tableBody.innerHTML = '<tr><td colspan="8">Error al cargar los datos</td></tr>';
        });
});
