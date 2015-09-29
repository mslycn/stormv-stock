package org.mokey.stormv.stock.data.dao;

import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
import org.mokey.stormv.stock.data.entities.YahooEntity;

import java.util.Date;

/**
 * SQLite 复权日K线数据 操作接口
 * Created by enousei on 9/29/15.
 */
public interface YahooDao extends BaseDao {
    @Update({"CREATE TABLE IF NOT EXISTS ${table}",
            "(Date TEXT primary key, Open REAL, Low REAL, High REAL, Close REAL, Volume DOUBLE, AdjClose DOUBLE)"})
    Integer createTable(@Param("table")String table);

    @Select("select count(*)=1 from ${table} where date = #{date} limit 1")
    boolean hasRecord(@Param("table")String table, @Param("date") String date);


    @Insert({"insert into ${table} (date, open, low, high, close, volume, adjClose)",
            "values(#{entity.date}, #{entity.open}, #{entity.low}, #{entity.high}, #{entity.close}, #{entity.volume}, #{entity.adjClose})"})
    boolean insert(@Param("table")String table, @Param("entity")YahooEntity entity);

    @Select("select * from ${table} where date = #{date} limit 1")
    YahooEntity query(@Param("table")String table, @Param("date")Date date);
}
