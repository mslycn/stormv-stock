package org.mokey.stormv.stock.data.dao;

import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
import org.mokey.stormv.stock.data.entities.KLineEntity;

/**
 * SQLite K线数据 操作接口
 * Created by enousei on 9/26/15.
 */
public interface KLineDao extends BaseDao{

    @Update({"CREATE TABLE IF NOT EXISTS ${table}",
            "(Date TEXT primary key, Open REAL, Low REAL, High REAL, Close REAL, Volume DOUBLE, Amount DOUBLE)"})
    Integer createTable(@Param("table")String table);

    @Select("select count(*)=1 from ${table} where date = #{date} limit 1")
    boolean hasRecord(@Param("table")String table, @Param("date") String date);

    @Insert({"insert into ${table} (date, open, low, high, close, volume, amount)",
            "values(#{kline.date}, #{kline.open}, #{kline.low}, #{kline.high}, #{kline.close}, #{kline.volume}, #{kline.amount})"})
    boolean insert(@Param("table")String table, @Param("kline")KLineEntity kline);

    @Select("select * from ${table} where date = #{date} limit 1")
    KLineEntity query(@Param("table") String table, @Param("date")String date);
}
