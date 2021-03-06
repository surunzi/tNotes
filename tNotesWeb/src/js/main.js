// Requirejs配置文件，主要是各模块路径的缩短
require.config({

    paths: {
        'Database': 'db/Database',
        'folderDb': 'db/folderDb',
        'noteDb'  : 'db/noteDb',

        'FolderModel': 'model/FolderModel',
        'NoteModel'  : 'model/NoteModel',
        'setting'    : 'model/setting',

        'folderCollection': 'collection/folderCollection',
        'noteCollection'  : 'collection/noteCollection',

        'contentViewer': 'view/contentViewer',
        'folderView'   : 'view/folderView',
        'noteList'     : 'view/noteList',
        'navbarView'       : 'view/navbarView',
        'hint'         : 'view/hint',

        'contentViewerRouter': 'router/contentViewerRouter',
        'folderRouter'       : 'router/folderRouter',
        'noteListRouter'     : 'router/noteListRouter',
        'navbarRouter'       : 'router/navbarRouter',

        'util': 'utils/util'
    }

});

// 程序的主入口，加载各视图的Router模块，同时作一些通用性的初始化
require(['contentViewerRouter', 'folderRouter',
        'noteListRouter', 'navbarRouter', 'utils/test'],
        function (contentViewerRouter, folderRouter,
        noteListRouter, navbarRouter, test) {

// 开启路由功能
Backbone.history.start();

// 绑定一般处理事件
$('body').on('click', 'a.disabled', function (e) {
    // 阻止被设置为disabled的链接产生作用
    e.preventDefault();
});

});