package esiot.module_lab_3_2;

class DataPoint {
	private float soilMoisture;
	private float temperature;
	
	public DataPoint(float soilMoisture, float temperature) {
		this.soilMoisture = soilMoisture;
		this.temperature = temperature;
	}

	public float getSoilMoisture() {
		return soilMoisture;
	}
	
	public float getTemperature() {
		return temperature;
	}
}
