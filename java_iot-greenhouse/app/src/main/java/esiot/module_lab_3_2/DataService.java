package esiot.module_lab_3_2;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;

import java.util.LinkedList;

public class DataService extends AbstractVerticle {

	private int port;
	private static final int MAX_SIZE = 10;
	private LinkedList<DataPoint> values;
	
	private SerialCommChannel channel;
	
	public DataService(int port) {
		values = new LinkedList<>();		
		this.port = port;
		try {
			this.channel = new SerialCommChannel(Integer.toString(port), 115200);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void start() {		
		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.post("/api/data").handler(this::handleAddNewData);
		router.get("/api/data").handler(this::handleGetData);		
		vertx
			.createHttpServer()
			.requestHandler(router)
			.listen(port);

		log("Service ready on port: " + port);
	}
	
	private void handleAddNewData(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		JsonObject res = routingContext.getBodyAsJson();
		if (res == null) {
			sendError(400, response);
		} else {
			float soilMoisture = res.getFloat("soilMoisture");
			float temperature = res.getFloat("temperature");

			values.addFirst(new DataPoint(soilMoisture, temperature));
			if (values.size() > MAX_SIZE) {
				values.removeLast();
			}

			log("POST - Current soil moisture: " + soilMoisture + ", temperature: " + temperature);

			try {
				sendDataToArduino(new DataPoint(soilMoisture, temperature));
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

			response.setStatusCode(200).end();
		}
	}
	
	private void handleGetData(RoutingContext routingContext) {
		if (values.isEmpty()) {
			routingContext.response()
				.setStatusCode(404)
				.end("No data available");
			return;
		}

		DataPoint latestValue = values.getFirst();
		JsonObject data = new JsonObject();
		data.put("soilMoisture", latestValue.getSoilMoisture());
		data.put("temperature", latestValue.getTemperature());

		routingContext.response()
			.putHeader("content-type", "application/json")
			.end(data.encodePrettily());
	}
	
	public LinkedList<DataPoint> getValues() {
		return values;
	}

	private void sendDataToArduino(DataPoint lv) throws InterruptedException {
		log("AFTER POST - sending data to Arduino - SM: " + lv.getSoilMoisture() + ", T: " + lv.getTemperature());
		DataPoint latestValue = lv;
		float soilMoisture = latestValue.getSoilMoisture();
		float temperature = latestValue.getTemperature();
		if (channel != null) {
			channel.sendMsg(soilMoisture + "," + temperature);
		}
	}

	private void sendError(int statusCode, HttpServerResponse response) {
		response.setStatusCode(statusCode).end();
	}

	private void log(String msg) {
		System.out.println("[DATA SERVICE] "+msg);
	}

}