package org.mokey.stormv.stock.data.dao;

import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
import org.mokey.stormv.stock.data.entities.SinaEntity;

import java.util.List;


/**
 * SQLite 新浪交易明细 操作接口
 * Created by enousei on 9/29/15.
 */
public interface SinaDao extends BaseDao {
    @Update({"CREATE TABLE IF NOT EXISTS ${table}",
            "(Date TEXT , Time TEXT, Price REAL, Change REAL, Volume INTEGER, Amount INTEGER, Type Text)"})
    Integer createTable(@Param("table")String table);

    @Select("select count(*)=1 from ${table} where date = #{date} and time = #{time} limit 1")
    boolean hasRecord(@Param("table")String table, @Param("date") String date, @Param("time")String time);

    @Insert({"insert into ${table} (date, time, price, change, volume, amount, type)",
            "values(#{entity.date}, #{entity.time}, #{entity.price}, #{entity.change}, #{entity.volume}, #{entity.amount}, #{entity.type})"})
    boolean insert(@Param("table")String table, @Param("entity")SinaEntity entity);

    @Select("select * from ${table} where date = #{date} and time = #{time}")
    List<SinaEntity> query(@Param("table")String table, @Param("date")String date);
}
