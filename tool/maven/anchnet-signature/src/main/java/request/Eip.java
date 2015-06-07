package request;

import java.util.HashMap;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: anchnet-002
 * Date: 15-3-29
 * To change this template use File | Settings | File Templates.
 */
public class Eip {

  public static Map<String,Object> allocateEips(){
    Map<String,Object> map = new HashMap<String, Object>();
    Map<String,Object> product = new HashMap<String, Object>();
    Map<String,Object> ip = new HashMap<String, Object>();
    ip.put("bw",1);
    ip.put("ip_group","eipg-00000000");
    ip.put("amount",1);

    product.put("ip",ip);

    map.put("product",product);
    map.put("project",86);
    return Base.putPublic(map, "AllocateEips");
  }

  public static Map<String,Object> describeEips(){
    Map<String,Object> map = new HashMap<String, Object>();
    //        map.put("eips",new String[]{"eip-ISNL5NUT"});
    map.put("status",new String[]{"suspended"});
    //        map.put("search_word","103.21.118.70");
    //        map.put("offset","");
    //        map.put("limit","");
    return Base.putPublic(map, "DescribeEips");
  }

  public static Map<String,Object> associateEip(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("eip","eip-IM0MNM31");
    map.put("instance","i-MHV0M73W");
    map.put("project","86");
    return Base.putPublic(map, "AssociateEip");
  }

  public static Map<String,Object> dissociateEips(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("eips",new String[]{"eip-E3QC37V8","eip-2RBX74RP"});

    return Base.putPublic(map, "DissociateEips");
  }

  public static Map<String,Object> changeEipsBandwidth(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("eips",new String[]{"eip-IM0MNM31"});
    map.put("bandwidth",2);
    map.put("project",86);
    return Base.putPublic(map, "ChangeEipsBandwidth");
  }

  public static Map<String,Object> releaseEips(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("eips",new String[]{"eip-7Y60H6WN","eip-FBCQCEO6"});
    //        map.put("project","pro-4QZCAFFW");
    return Base.putPublic(map, "ReleaseEips");
  }

  public static Map getSyncImpl() {
    throw new RuntimeException("require spring configure");
  }
}
