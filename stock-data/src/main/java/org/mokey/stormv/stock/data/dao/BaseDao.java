package org.mokey.stormv.stock.data.dao;

import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

/**
 * SQLite数据库操作公共接口
 * Created by enousei on 9/29/15.
 */
public interface BaseDao {
    @Select("select count(*)=1 from sqlite_master where type='table' and name=#{table}")
    boolean existsTable(@Param("table")String table);

    @Update({"CREATE INDEX ${indexName} on ${table}(${column})"})
    void createIndex(@Param("table")String table, @Param("column")String column, @Param("indexName")String indexName);

    @Select("select count(*)=1 from sqlite_master where type='index' and name=#{indexName}")
    boolean hasIndex(@Param("indexName")String indexName);

    @Update("DROP TABLE IF EXISTS ${table}")
    void dropTable(@Param("table")String table);

    @Update("DROP INDEX IF EXISTS ${indexName}")
    void dropIndex(@Param("indexName")String indexName);

    @Update("DELETE FROM ${table}")
    void deleteTable(@Param("table")String table);
}
