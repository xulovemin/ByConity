SET output_format_write_statistics = 0;
SELECT (case when audit_object_type = '站内计划' and first_item in ('头条广告' ,'延时审核队列' ,'媒介广告' ,'穿山甲' ,'头条行业广告' ,'抖音广告' ,'大客户广告' ,'分创意队列' ) and second_item not in ('dou+号外广告') then '站内计划_非召回' when first_item in ('程序化广告') and second_item not in ('dsp抖音召回','dpa商品审核') then '程序化广告' when audit_object_type = '鲁班商品' then '鲁班商品审核' when second_item in('建站小程序','第三方小程序') then '小程序'when first_item in ('视频前置审核','视频前置审核（新）' )then '视频前置审核' when first_item='图片前置审核' then '图片前置审核' when first_item='标题前置审核' then '标题前置审核' when first_item='建站前置审核' then '建站前置审核' when object_type=1000005 and second_item not in ('直播切片审核' ,'社区处罚直播' ,'品牌直播切片审核' ,'品牌社区处罚直播' ,'直播切片抽样' ,'企业号-清退队列' ,'dou+直播切片' ,'赠送视频','直播间视频切片' ,'品牌假货直播切片' ,'假货直播切片' ,'穿山甲媒体APP' ) then '其他物料' end) AS _1700002407992, (sum(manual_delay_time_total)/sum(valid_audit_cnt+null_valid_audit_cnt)/60) AS _1700003698790 FROM `aeolus_data_db_aeolus_delta_202002`.`aeolus_data_table_29307_prod` SAMPLE 1.0 WHERE (((((p_date >= '2021-08-04') AND (p_date <= '2021-08-10')) AND ((first_item) IS NOT NULL) AND ((case when object_category=1000115 then '鲁班落地页审核'   when object_category=1000056 then 'dsp抖音广告（新）'    when object_category=1000057 then 'dsp创建广告（新）' else    second_item end) IN (('大客户分级'), ('电商平台分级'))) AND ((case when audit_object_type = '站内计划' and first_item in ('头条广告' ,'延时审核队列' ,'媒介广告' ,'穿山甲' ,'头条行业广告' ,'抖音广告' ,'大客户广告' ,'分创意队列' ) and second_item not in ('dou+号外广告') then '站内计划_非召回' when first_item in ('程序化广告') and second_item not in ('dsp抖音召回','dpa商品审核') then '程序化广告' when audit_object_type = '鲁班商品' then '鲁班商品审核' when second_item in('建站小程序','第三方小程序') then '小程序'when first_item in ('视频前置审核','视频前置审核（新）' )then '视频前置审核' when first_item='图片前置审核' then '图片前置审核' when first_item='标题前置审核' then '标题前置审核' when first_item='建站前置审核' then '建站前置审核' when object_type=1000005 and second_item not in ('直播切片审核' ,'社区处罚直播' ,'品牌直播切片审核' ,'品牌社区处罚直播' ,'直播切片抽样' ,'企业号-清退队列' ,'dou+直播切片' ,'赠送视频','直播间视频切片' ,'品牌假货直播切片' ,'假货直播切片' ,'穿山甲媒体APP' ) then '其他物料' end) = ('站内计划_非召回')) AND ((case when toDayOfWeek(p_date)= 6 then '周末' when toDayOfWeek(p_date)= 7 then '周末' else '工作日'end) IN (('周末'), ('工作日')))))) GROUP BY case when audit_object_type = '站内计划' and first_item in ('头条广告' ,'延时审核队列' ,'媒介广告' ,'穿山甲' ,'头条行业广告' ,'抖音广告' ,'大客户广告' ,'分创意队列' ) and second_item not in ('dou+号外广告') then '站内计划_非召回' when first_item in ('程序化广告') and second_item not in ('dsp抖音召回','dpa商品审核') then '程序化广告' when audit_object_type = '鲁班商品' then '鲁班商品审核' when second_item in('建站小程序','第三方小程序') then '小程序'when first_item in ('视频前置审核','视频前置审核（新）' )then '视频前置审核' when first_item='图片前置审核' then '图片前置审核' when first_item='标题前置审核' then '标题前置审核' when first_item='建站前置审核' then '建站前置审核' when object_type=1000005 and second_item not in ('直播切片审核' ,'社区处罚直播' ,'品牌直播切片审核' ,'品牌社区处罚直播' ,'直播切片抽样' ,'企业号-清退队列' ,'dou+直播切片' ,'赠送视频','直播间视频切片' ,'品牌假货直播切片' ,'假货直播切片' ,'穿山甲媒体APP' ) then '其他物料' end LIMIT 1000 FORMAT JSONCompact  SETTINGS fallback_to_stale_replicas_for_distributed_queries=0,max_replica_delay_for_distributed_queries = 1