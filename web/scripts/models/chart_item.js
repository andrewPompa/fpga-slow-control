class ChartItem {
    constructor(id, name, interval, dataSets) {
        this.id = id;
        this.name = name;
        this.interval = interval;
        this.dataSets = dataSets;
        this.chart = null;
    }

    buildCanvas() {
        return `
            <div class="col-xl-6">
                <canvas id="chart_${this.id}" ></canvas>
            </div>
        `;
    }

    valueForConfiguration() {
        return {
            id: this.id,
            name: this.name,
            interval: this.interval,
            series: this.dataSets,
        };
    }

    setLabels(labels) {
        this.chart.data.labels = labels;
    }

    setSeries(id, data) {
        console.log(data);
        const foundDataset = this.chart.data.datasets.find(dataset => dataset.id === id);
        if (!foundDataset) {
            console.log('cannot find dataset: ' + id);
            return;
        }
        foundDataset.data = data;
        this.chart.update();
    }

    buildChart(withInterval) {
        const ctx = $(`#chart_${this.id}`)[0].getContext('2d');
        const datasets = this.dataSets.map(dataset => {
            const colour = Math.floor(Math.random() * 255) + ', ' + Math.floor(Math.random() * 255) + ', ' + Math.floor(Math.random() * 255);
            return {
                label: dataset.name,
                backgroundColor: `rgba(${colour}, 0.5)`,
                borderColor: `rgb(${colour})`,
                data: [],
                address: dataset.address,
                dataType: dataset.dataType,
                formula: dataset.formula,
                id: dataset.id,
                deltaValue: dataset.deltaValue,
                results: []
            };
        });
        this.chart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: [],
                datasets: datasets
            },
            options: {
                title: {display: true, text: this.name}
            }
        });
        if (withInterval === true) {
            this.intervalId = setInterval(() => this.tickFunction(), this.interval);
        }
    }

    tickFunction() {
        this.chart.data.labels.push(currentTimeInMillis());
        this.chart.data.datasets.forEach(dataset => {
            if (dataset.dataType === dateType.hex) {
                wordService.getInt(dataset.address, (value) => {
                    if (dataset.deltaValue === true) {
                        const previous = dataset.results.length > 0 ? dataset.results[dataset.results.length - 1] : value;
                        dataset.results.push(value);
                        value = value - previous;
                    }
                    this.addData(value, dataset)
                });
            } else if (dataset.dataType === dateType.math) {
                wordService.getMath(dataset.address, dataset.formula, (value) => {
                    if (dataset.deltaValue === true) {
                        const previous = dataset.results.length > 0 ? dataset.results[dataset.results.length - 1] : value;
                        dataset.results.push(value);
                        value = value - previous;
                    }
                    this.addData(value, dataset)
                });
            }

        });

    }

    addData(value, dataset) {
        dataset.data.push(value);
        this.chart.update();
    }

    removeInterval() {
        clearInterval(this.intervalId);
    }

}