
import com.google.gson.Gson;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.impl.conn.PoolingHttpClientConnectionManager;
import org.apache.http.params.CoreConnectionPNames;
import request.*;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.security.KeyPair;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: anchnet-002
 * Date: 15-3-20
 * To change this template use File | Settings | File Templates.
 */
public class Http {

  String upApiUrl = "http://api.51idc.com/cloud/api/iaas";

  CloseableHttpClient httpClient = null;

  public String request(String params) {
    PoolingHttpClientConnectionManager cm = new PoolingHttpClientConnectionManager();
    httpClient = HttpClients.custom().setConnectionManager(cm).build();
    HttpPost post = new HttpPost(this.upApiUrl);
    String result = "";
    try {
      post.addHeader("Content-type", "application/json");
      String sig = Signature.signature(params, Constant.SECRET_KEY);
      String json = Signature.trim(params);
      post.addHeader("signature", sig);
      post.setEntity(new StringEntity(json, "application/json", "utf-8"));
      System.out.println(sig);
      System.out.println(json);
      result = httpClient.execute(post, new BasicResponseHandler());
      return result;
    } catch (IOException e) {
      e.printStackTrace();
      return null;
    } finally {
      try {
        httpClient.close();
      } catch (Exception e) {
        e.printStackTrace();
      }
    }
  }
}
